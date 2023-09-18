#include <Arduino.h>

#include "TftScreen.h"
//#include "Screen.h"
#include "GpsM8N.h"
#include "LinearSuspension.h"
#include "SdUnit.h"
#include "Track.h"
#include "Session.h"
#include "Revolution.h"


//Pins
byte txGpsPin = 10;  // Pines Para mega es (10,9), Micro (9,8)
byte rxGpsPin = 9;
const byte pinTachInterrupt = 19;  // Interrupt 0 (digital pin 2) D19
const byte pinMenu = 3;           // Interrupt 0 (digital pin 2)
uint8_t pinFrontlinearSuspension = A0;
uint8_t pinRearlinearSuspension = A1;
int next = 2;
int CS_PIN = 53;

//Class
Gps gps;
//Screen screen;
LinearSuspension FrontlinearSuspension(pinFrontlinearSuspension);
LinearSuspension RearlinearSuspension(pinRearlinearSuspension);
SdUnit sd;
Session session("Medellin");
Track *tracks[9];
Revolution rev;
TftScreen screen;

int trackNear = -1;


int option = 0;
int enter = 0;
long lastDebounceTime = 0;  // the last time the button was pushed
long lastScreenRefresh = 0;

long beginLapTimer = 0;
int sat = -2;

void setup() {
  pinMode(pinTachInterrupt, INPUT_PULLUP);  // enable internal pullup for tach pin
  pinMode(pinMenu, INPUT_PULLUP);           // enable internal pullup for tach pin
  pinMode(next, INPUT_PULLUP);
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();
  tracks[0] = new Track("Medellin ", -75.6056060, 6.1523671, 9);
  tracks[1] = new Track("Manizales ", -75.478615, 5.032166, 9);
  tracks[2] = new Track("Tocancipa ", 6.1523671, -75.685760, 9);
  tracks[3] = new Track("Finca ", -75.685753, 5.104020, 9);



  beginLapTimer = millis();

   session.addLap(beginLapTimer);  //Borrar

  attachInterrupt(digitalPinToInterrupt(pinTachInterrupt), countRPM, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinMenu), optionClick, RISING);
    attachInterrupt(digitalPinToInterrupt(next), enterClick, RISING);
}


void loop() {
  defaultMenu();

  /** Menu **/
  int selected = option - 3;
  screenMenu(option);
  enter=0;
}
/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ Function that works with the screen  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/

void screenMenu(int option) {
  String text = "";
  // Menu
  switch (option) {
    case (0):  //Home
      if (sat < 0) {
        sat = gps.readGps();
        //Serial.println(date[0]);
        screen.printHome(sat, "Buscando Satelite");
        break;
      } else {
        if (trackNear == -1) {
          screen.printHome(sat, "Buscando Pista");
            break;
        }else{
          option=1;
        }
      }
    case (1):  //LapTimer
      sat = gps.readGps();
      if ((millis() - lastScreenRefresh) > 250) {
        text += gps.getDistance(tracks[trackNear]->getStartLong(), tracks[trackNear]->getStartLat());
        text += "m     ";
        screen.printLaptimer(session.getTime(), String(sat), gps.getSpeed(), String(session.getLap()), text);
        lastScreenRefresh = millis();
      }
      break;
    case (2):  // Revolutions
      if ((millis() - rev.getLastRpmRefresh()) > rev.getRefreshInterval()) {
        screen.printRPMS(String(rev.getRPM()));
        rev.setLastRpmRefresh(millis());
      }
      break;
    case (3):  // Suspention
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Delanter: ";
        text += FrontlinearSuspension.getLinearSensorInfo();
        text += "    Trasera: ";
        text += RearlinearSuspension.getLinearSensorInfo();
        screen.printSuspension(String(FrontlinearSuspension.getLinearSensorInfo()), String(RearlinearSuspension.getLinearSensorInfo()));
        lastScreenRefresh = millis();
      }
      break;
    case (4):  //Summary
      sat = gps.readGps();
      if (sat >= 0) {
        if ((millis() - lastScreenRefresh) > 500) {
          screen.printText(session.getSummary());
        }
      } else {
        option++;
      }
      break;
    /*case (2):  //Menu Configuracion
      screen.printMenu(0);
      break;
    case (3):  //Menu Suspension
      if (enter == 1) {
        option = 7;
        enter = 0;
      } else
        screen.printMenu(1);
      break;
    case (4):  //Menu RPMs
      if (enter == 1) {
        option = 8;
        enter = 0;
      } else
        screen.printMenu(2);
      break;
    case (5):  //Menu Horometro
      screen.printMenu(3);
      break;
    case (6):  //Menu Llantas
      screen.printMenu(4);

      break;
    */
    case (5):  //
      sat = gps.readGps();
      if (sat >= 0) {
        text += "   Logitud: ";
        text += String(gps.getLongitude(), 6);
        text += " Latitud: ";
        text += String(gps.getLatitude(), 6);

        screen.printText(text);
      } else {
        option++;
      }
      break;
    case (14):
      sat = gps.readGps();
      if ((millis() - beginLapTimer) > 5000) {
        screen.printLastLap(session.getLasLap(), session.getLap());
        option = 1;
      }
      break;
    default:
      Serial.println("Default");
      //screen.printHome(sat, "");
  }
}

/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ Funcion encargada de la pantalla que ve el usuario.   /*/
/*////////////////////////////////////////////////////////////////////////////////////*/
void defaultMenu() {
  /**Clicks
  if ((millis() - lastDebounceTime) > 50000) {
    option = 0;
    enter = 0;
  }*/
  if ((option >= 4) || (option <= 0))
    option = 0;
  /*Esto puede cambiar si se pone una pantalla sin GPS.*/
  if (sat > 0) {
    option = 1;
    /* Search Track */
    if (trackNear == -1) {
      int limite = (sizeof(tracks) / sizeof(tracks[0]));
      for (int i = 0; i < limite; i++) {
        if (gps.getDistance(tracks[i]->getStartLong(), tracks[i]->getStartLat()) < 500) {
          trackNear = i;
        }
      }
    } else {
      /*Logic of sessions*/
      if (gps.getDistance(tracks[trackNear]->getStartLong(), tracks[trackNear]->getStartLat()) < tracks[trackNear]->getWidth()
          && sat > 1
          // && gps.getSpeed() > 5.0
          && (millis() - beginLapTimer > 9000)) {
        beginLapTimer = millis();
        session.addLap(beginLapTimer);  //Inicia Vuelta
        option = 14;
      }
    }
  }


}
//////////////////////////////////////////////////////////////////////////////////////
// FUNCION ENCARGADA DE CONTAR LOS PULSOS CADA VEZ QUE SE PRODUCE UNA INTERRUPCION  //
//////////////////////////////////////////////////////////////////////////////////////

void countRPM() {
  Serial.println("Pulse");
  rev.addPulse();
}

/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ FUNCION ENCARGADA DE CONTAR LOS PULSOS CADA VEZ QUE SE PRODUCE UNA INTERRUPCION  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/
void optionClick() {


  if ((millis() - lastDebounceTime) > 400) {
    Serial.print(option);
    option++;
    lastDebounceTime = millis();
    Serial.print(" Suma ");
    enter = 0;
  } else {
    if ((millis() - lastDebounceTime) > 100) {
      Serial.print("Doble click ");
      enter = 1;
      option--;
      lastDebounceTime = millis();
    }
  }

  Serial.print("option = ");
  Serial.print(option);

  Serial.print(". enter = ");
  Serial.println(enter);
}

/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ FUNCION ENCARGADA DE CONTAR LOS PULSOS CADA VEZ QUE SE PRODUCE UNA INTERRUPCION  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/
void enterClick(){
 Serial.println("Enter");
 enter=1;
}

/*********************************************
*** 
**********************************************/
void menuEnter(int option, int enter) {
}
