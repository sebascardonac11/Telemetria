#include <Arduino.h>

#include "Screen.h"
#include "Gps.h"
#include "LinearSuspension.h"
#include "SdUnit.h"
#include "Track.h"
#include "Session.h"

const byte pinTachInterrupt = 2;  // Interrupt 0 (digital pin 2)
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

int state = 0;
int option = 0;
long lastDebounceTime = 0;  // the last time the button was pushed
long lastScreenRefresh = 0;
long lastRPMRefresh = 0;
long beginLapTimer = 0;
int minutos = 0;

volatile int RPMpulses = 0;  //Variable que almacena los pulsos en bujía

void setup() {
  pinMode(pinTachInterrupt, INPUT_PULLUP);
  pinMode(next, INPUT);
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();

  beginLapTimer = millis();


  pinMode(2, INPUT_PULLUP);  // enable internal pullup for tach pin
  attachInterrupt(digitalPinToInterrupt(pinTachInterrupt), countRPM, FALLING);
}

void loop() {
  int sat = gps.readGps();
  if (gps.getDistance(6.1523671, -75.6056060) < 9 && sat > 1) {
    beginLapTimer = millis();
    minutos = 0;
    session.addLap(millis());
  }
  session.lapTimer(millis());

  //***********************Revoluciones.


  if ((millis() - lastRPMRefresh) > 250 && (RPMpulses > 0)) {
    Serial.print("RMPs: ");
    Serial.println(getRPM());
    //   RPMpulses = 0;
    lastRPMRefresh = millis();
  }

  //***********************Revoluciones.
  if (digitalRead(next) == HIGH) {
    if ((millis() - lastDebounceTime) > 500) {
      option++;
      if (option > 2)
        option = 0;
      Serial.print("option = ");
      Serial.println(option);
    }
    lastDebounceTime = millis();
  }
  String text = "";
  String date;
  date = gps.getDate();
  // Menu
  switch (option) {
    case (0):  //Home
      if (sat < 0) {
        screen.printHome(sat);
        break;
      }
    case (1):  //LapTimer
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Distancia: ";
        text += gps.getDistance(6.1523671, -75.6056060);
        text += "m     ";
        //screen.printLaptimer(cronometro(beginLapTimer), String(sat), gps.getSpeed(), text);
        screen.printLaptimer(session.getTime(), String(sat), gps.getSpeed(), text);
        lastScreenRefresh = millis();
      }
      break;
    case (2):  // Suspention
      if ((millis() - lastScreenRefresh) > 500) {
        text += "Delanter: ";
        text += FrontlinearSuspension.getLinearSensorInfo();
        text += "    Trasera: ";
        text += RearlinearSuspension.getLinearSensorInfo();
        screen.printSuspension(text);
        lastScreenRefresh = millis();
      }
      break;
    case (3):  //
      Serial.println("Opt 3");
      break;
    default:
      screen.printHome(sat);
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
  //Serial.print("Entrando a contar RPMS.");
  RPMpulses++;
  //Serial.println(RPMpulses);
}


/////////////////////////////////////////////////////
// FUNCION ENCARGADA DE CALCULAR LAS REVILUCIONES  //
/////////////////////////////////////////////////////

int getRPM() {
  byte cilindros = 1;   
  int refreshInterval = 250;        // milisegundos refresco                                                                      // (pulsos por revolucion = 2 * cylinders / cycles)
  byte tiempos = 4;                                                                           // tipo motor
  int RPM = int(RPMpulses * (60000.0 / float(refreshInterval)) * tiempos / cilindros / 2.0);  // calculate RPM
  //int RPM = int(RPMpulses * (60000.0 / float(refreshInterval)) * 1 ); // calculate RPM
  RPMpulses = 0;             // reset pulse count to 0
  return RPM;
}
