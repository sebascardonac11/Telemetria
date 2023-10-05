#include <Arduino.h>


#include "Memory.h"
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
const byte pinTachInterrupt = 19;  // Interrupt 0 (digital pin 19) D19
const byte pinMenu = 3;            // Interrupt 0 (digital pin 3)
const byte pinEnter = 2;           // Interrupt 0 (digital pin 2)
uint8_t pinFrontlinearSuspension = A0;
uint8_t pinRearlinearSuspension = A1;
int CS_PIN = 53;

//Class
Gps gps;
//Screen screen;
LinearSuspension FrontlinearSuspension(pinFrontlinearSuspension);
LinearSuspension RearlinearSuspension(pinRearlinearSuspension);
SdUnit sd;
Session session("Manizales");
Track *tracks[9];
Revolution rev;
TftScreen screen;
Memory memory;

int trackNear = -1;


int option = 0;
int defOption = 0;
int enter = 0;
long lastDebounceTime = 0;  // the last time the button was pushed
long lastScreenRefresh = 0;
int menu = -1;
float hours = 0.0;

long beginLapTimer = 0;
int sat = -2;

void setup() {
  pinMode(pinTachInterrupt, INPUT_PULLUP);  // enable internal pullup for tach pin
  pinMode(pinMenu, INPUT_PULLUP);           // enable internal pullup for tach pin
  pinMode(pinEnter, INPUT_PULLUP);          // enable internal pullup for tach pin
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();
  tracks[0] = new Track("Manizales ", -75.478615, 5.032166, 9);
  tracks[1] = new Track("Medellin ", -75.60573033, 6.15239417, 9);
  tracks[2] = new Track("Tocancipa ", 6.1523671, -75.685760, 9);
  tracks[3] = new Track("Finca ", -75.685753, 5.104020, 9);

  //memory.setHour(14.2 );

  beginLapTimer = millis();

  //session.addLap(beginLapTimer);  //Borrar

  hours = memory.getHour();

  attachInterrupt(digitalPinToInterrupt(pinTachInterrupt), countRPM, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinMenu), optionClick, RISING);
  attachInterrupt(digitalPinToInterrupt(pinEnter), enterClick, RISING);
}


void loop() {
  //Serial.println(digitalRead(pinEnter));
  //Serial.println(tt);
  defaultMenu();
  /** Menu **/
  int selected = option - 3;
  screenMenu(option);
  enter = 0;
}
/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ Function that works with the screen  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/

void screenMenu(int option) {
  String text = "";
  // Menu
  switch (option) {
    case (0):  //Home
      sat = gps.readGps();
      if (sat < 0) {
        screen.printHome(sat, hours, "");
        break;
      } else {
        if (trackNear == -1) {
          screen.printHome(sat, hours, "Buscando Pista");
          break;
        }
        defOption = 1;
      }
    case (1):  //LapTimer
      sat = gps.readGps();
      if ((millis() - lastScreenRefresh) > 250) {
        text += gps.getDistance(tracks[trackNear]->getStartLong(), tracks[trackNear]->getStartLat());
        text += "m     ";
        screen.printLaptimer(session.getTime(), String(sat), gps.getSpeed(), String(session.getLap()),
                             tracks[trackNear]->getName(), hours,gps.getTime(), text);
        lastScreenRefresh = millis();
      }
      break;
    case (2):  //Menu
      sat = gps.readGps();
      if ((millis() - lastScreenRefresh) > 500) {
        menu = screen.printMenu(menu);
        lastScreenRefresh = millis();
        // Serial.print("Menu: ");
        //Serial.println(menu);
      }
      break;


    case (10):  // Suspention
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Delanter: ";
        text += FrontlinearSuspension.getLinearSensorInfo();
        text += "    Trasera: ";
        text += RearlinearSuspension.getLinearSensorInfo();
        screen.printSuspension(String(FrontlinearSuspension.getLinearSensorInfo()), String(RearlinearSuspension.getLinearSensorInfo()));
        lastScreenRefresh = millis();
      }
      break;
    case (11):  // Revolutions
      if ((millis() - rev.getLastRpmRefresh()) > rev.getRefreshInterval()) {
        screen.printRPMS(String(rev.getRPM()));
        rev.setLastRpmRefresh(millis());
      }
      break;
    case (12):  //Summary
      sat = gps.readGps();
      if (sat >= 0) {
        if ((millis() - lastScreenRefresh) > 500) {
          screen.printText(session.getSummary());
          lastScreenRefresh = millis();
        }
      } else {
        option++;
      }
      break;
    case (13):  //
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
  if (((option >= 3) || (option <= 0) || (menu == -1)) && (option <= 9))
    option = defOption;
  /*Esto puede cambiar si se pone una pantalla sin GPS.*/
  if (sat >= 0) {
    Serial.println(gps.getDate());  //10/04/2023 19:12:19
    /* Search Track */
    if (trackNear == -1) {
      int limite = (sizeof(tracks) / sizeof(tracks[0]));
      float distance = gps.getDistance(tracks[0]->getStartLong(), tracks[0]->getStartLat());

      trackNear = 0;
      for (int i = 0; i < limite; i++) {
        //  Serial.println("Track Distance");
        //  Serial.println(gps.getDistance(tracks[i]->getStartLong(), tracks[i]->getStartLat()));
        if (gps.getDistance(tracks[i]->getStartLong(), tracks[i]->getStartLat()) <= distance) {
          distance = gps.getDistance(tracks[i]->getStartLong(), tracks[i]->getStartLat());
          trackNear = i;
        }
      }
      session.setTrackName(tracks[trackNear]->getName());
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
/*/ This fuction is trigger when click in a option button  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/
void optionClick() {
  if ((millis() - lastDebounceTime) > 400) {
    enter = 0;
    if (option <= 1) {
      menu = 0;
      option++;
    } else {
      if (option >= 9) { option = defOption; }
      menu++;
    }
    lastDebounceTime = millis();
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

  Serial.print(". menu = ");
  Serial.println(menu);
}

/*////////////////////////////////////////////////////////////////////////////////////*/
/*/ FUNCION ENCARGADA DE CONTAR LOS PULSOS CADA VEZ QUE SE PRODUCE UNA INTERRUPCION  /*/
/*////////////////////////////////////////////////////////////////////////////////////*/
void enterClick() {
  Serial.println("Enter");
  enter = 1;
  switch (menu) {
    case (0):
      option = 10;
      break;
    case (1):
      option = 11;
      break;
  }
}

/*********************************************
*** 
**********************************************/
void menuEnter(int option, int enter) {
}
