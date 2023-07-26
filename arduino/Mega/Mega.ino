#include <Arduino.h>


#include "Screen.h"
#include "Gps.h"
#include "LinearSuspension.h"
#include "SdUnit.h"
#include "Track.h"
#include "Session.h"

uint8_t pinFrontlinearSuspension = A0;
uint8_t pinRearlinearSuspension = A1;
int next = 7;
int CS_PIN = 53;

Gps gps;
Screen screen;
LinearSuspension FrontlinearSuspension(pinFrontlinearSuspension);
LinearSuspension RearlinearSuspension(pinRearlinearSuspension);
SdUnit sd;

int state = 0;
int option = 0;
long lastDebounceTime = 0;  // the last time the button was pushed
long beginLapTimer = 0;
int minutos = 0;

void setup() {
  pinMode(next, INPUT);
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();

  beginLapTimer = millis();
}

void loop() {
  int sat = gps.readGps();
  if (gps.getDistance(6.1523671, -75.6056060) < 1.5 && sat >1) {
    beginLapTimer = millis();
  }

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

  // Menu
  switch (option) {
    case (0):  //Home
      screen.printHome(sat);
      break;
    case (1):  //LapTimer
      /*text += "|Lat: ";
      text += String(gps.getLatitude(), 7);
      text += ",Long: ";
      text += String(gps.getLongitude(), 7);*/
      text += "Distancia: ";
      text += gps.getDistance(6.1523671, -75.6056060);
      text += "      Fecha: ";
      text += gps.getDate();
      screen.printLaptimer(cronometro(beginLapTimer), String(sat), gps.getSpeed(), text);
      break;
    case (2):  // Suspention
      text += FrontlinearSuspension.getLinearSensorInfo();
      screen.printSuspension(text);
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
