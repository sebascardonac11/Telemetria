#include <Arduino.h>

#include "Screen.h"
#include "GpsM8N.h"
#include "LinearSuspension.h"
#include "SdUnit.h"
#include "Track.h"
#include "Session.h"

//Pins
byte txGpsPin = 10;  // Pines Para mega es (10,9), Micro (9,8)
byte rxGpsPin = 9;
const byte pinTachInterrupt = 2;  // Interrupt 0 (digital pin 2)
const byte pinMenu = 3;           // Interrupt 0 (digital pin 2)
uint8_t pinFrontlinearSuspension = A0;
uint8_t pinRearlinearSuspension = A1;
int next = 8;
int CS_PIN = 53;

Gps gps;
Screen screen;
LinearSuspension FrontlinearSuspension(pinFrontlinearSuspension);
LinearSuspension RearlinearSuspension(pinRearlinearSuspension);
SdUnit sd;
Session session("Medellin");
Track *tracks[9];

int state = 0;
int option = 0;
int enter = 0;
long lastDebounceTime = 0;  // the last time the button was pushed
long lastScreenRefresh = 0;
long lastRPMRefresh = 0;
long beginLapTimer = 0;
int minutos = 0;
int sat = -2;

volatile int RPMpulses = 0;  //Variable que almacena los pulsos en bujía

void setup() {
  pinMode(pinTachInterrupt, INPUT_PULLUP);  // enable internal pullup for tach pin
  pinMode(pinMenu, INPUT_PULLUP);           // enable internal pullup for tach pin
  pinMode(next, INPUT);
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();
  tracks[0] = new Track("Medellin ", 6.1523671, -75.6056060, 9);
  tracks[1] = new Track("Manizales ", 6.1523671, -75.6056060, 9);
  tracks[2] = new Track("Tocancipa ", 6.1523671, -75.685760, 9);
  tracks[3] = new Track("Finca ", -75.685753, 5.104020, 9);

  beginLapTimer = millis();
  attachInterrupt(digitalPinToInterrupt(pinTachInterrupt), countRPM, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinMenu), optionClick, RISING);
  session.lapTimer();
  //Serial.println(tracks[2]->getName());
}


void loop() {

  if (gps.getDistance(tracks[3]->getStartLong(), tracks[3]->getStartLat()) < tracks[3]->getWidth() && 
  sat > 1 
  /* && gps.getSpeed() > 5.0 
    ( millis() - lastScreenRefresh >5000 )
  */
  ) {
    beginLapTimer = millis();
    minutos = 0;
    session.addLap(beginLapTimer);  //Inicia Vuelta
  }

  /**Clicks*/
  if ((millis() - lastDebounceTime) > 50000) {
    option = 0;
    enter = 0;
  }
  /**Clicks*/
  String text = "";
  String date = "Fecha";
  int selected = option - 3;
  // Menu
  switch (option) {
    case (0):  //Home
      if (sat < 0) {
        sat = gps.readGps();
        date = gps.getDate();
        //Serial.println(date[0]);
        screen.printHome(sat, date);
        break;
      }else{
        option =1;
      }
    case (1):  //LapTimer
      sat = gps.readGps();
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Distancia: ";
        text += gps.getDistance(tracks[3]->getStartLong(), tracks[3]->getStartLat());
        text += "m     ";
        screen.printLaptimer(session.getTime(), String(sat), gps.getSpeed(), String(session.getLap()), text);
        lastScreenRefresh = millis();
        //Serial.println(session.getTime());
      }
      break;
    case (2):  //Menu Configuracion
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
    case (7):  // Suspention
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Delanter: ";
        text += FrontlinearSuspension.getLinearSensorInfo();
        text += "    Trasera: ";
        text += RearlinearSuspension.getLinearSensorInfo();
        screen.printSuspension(text);
        lastScreenRefresh = millis();
      }
      break;
    case (8):  // Revolutions
      text += " Pulsos cada 10s : ";
      text += RPMpulses;
      screen.printRPMS(text);
      if ((millis() - lastRPMRefresh) > 10000 && (RPMpulses > 0)) {
        //Serial.print("RMPs: ");
        //Serial.println(getRPM());
        RPMpulses = 0;
        lastRPMRefresh = millis();
      }
      break;
    case (9):  // Revolutions
      sat = gps.readGps();
      text += "   Logitud: ";
      text += String(gps.getLongitude(), 6);
      text += " Latitud: ";
      text += String(gps.getLatitude(), 6);

      screen.printText(text);

      break;
    default:
      Serial.println("Default");
      screen.printHome(sat, date);
  }
}


/**

*/
String cronometro(long Imillis) {

  int segundos = 0;
  long diff = (millis() - Imillis);
  int centesimos = 0;
  String lapTimer = "0:00:000";
  segundos = (diff / 1000);
  centesimos = (diff - (segundos * 1000));
  segundos = segundos - (minutos * 60);
  if (segundos >= 60) {
    segundos = 0;
    minutos++;
  }
  lapTimer = (minutos);
  lapTimer += (":");
  lapTimer += (segundos);
  lapTimer += (":");
  lapTimer += (centesimos);
  /*
  Serial.print(lapTimer);
  Serial.print(".           diff ");
  Serial.print(diff);
  Serial.print(".           Inicial ");
  Serial.println(Imillis);*/
  return (lapTimer.substring(0, 7));
}
//////////////////////////////////////////////////////////////////////////////////////
// FUNCION ENCARGADA DE CONTAR LOS PULSOS CADA VEZ QUE SE PRODUCE UNA INTERRUPCION  //
//////////////////////////////////////////////////////////////////////////////////////

void countRPM() {

  RPMpulses++;
  Serial.print("Entrando a contar RPMS.");
  Serial.println(RPMpulses);
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
    if ((millis() - lastDebounceTime) > 200) {
      Serial.print("Doble click ");
      enter = 1;
      option--;
      lastDebounceTime = millis();
    }
  }
  if ((option >= 10) || (option <= 0))
    option = 0;
  Serial.print("option = ");
  Serial.print(option);

  Serial.print(". enter = ");
  Serial.println(enter);
}

/////////////////////////////////////////////////////
// FUNCION ENCARGADA DE CALCULAR LAS REVILUCIONES  //
/////////////////////////////////////////////////////

int getRPM() {
  byte cilindros = 1;
  int refreshInterval = 250;                                                                  // milisegundos refresco                                                                      // (pulsos por revolucion = 2 * cylinders / cycles)
  byte tiempos = 4;                                                                           // tipo motor
  int RPM = int(RPMpulses * (60000.0 / float(refreshInterval)) * tiempos / cilindros / 2.0);  // calculate RPM
  //int RPM = int(RPMpulses * (60000.0 / float(refreshInterval)) * 1 ); // calculate RPM
  RPMpulses = 0;  // reset pulse count to 0
  return RPM;
}

/*********************************************
*** 
**********************************************/
void menuEnter(int option, int enter) {
}
