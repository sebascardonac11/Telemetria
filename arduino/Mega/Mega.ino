#include <Arduino.h>


#include "Screen.h"
#include "Gps.h"
#include "LinearSuspension.h"
#include "SdUnit.h"
#include "Track.h"

int pinFrontlinearSuspension = analogRead(A0);
int pinRearlinearSuspension = analogRead(A1);
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

void setup() {
  pinMode(next, INPUT);
  pinMode(CS_PIN, OUTPUT);

  Serial.begin(115200);

  screen.init();
  sd.init();
}

void loop() {
  int sat = gps.sincroSatellites();

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

  // Menu
  switch (option) {
    case (0):  //Home
      Serial.println(option);
      screen.printHome(sat);
      break;
    case (1):  //
      Serial.println(option);
      String text = "";
      text += "Sat:";
      text += gps.getSatellite();
      text += "|Lat: ";
      text += String(gps.getLatitude(), 6);
      text += ",Long: ";
      text += String(gps.getLongitude(), 6);
      text += "      Distance";
      text += gps.getDistance(6.151369, -15.605492);
      screen.printLaptimer(text);
      break;
    case (2): //
      Serial.println("Opt 2");
      String suspention = "";
      suspention += FrontlinearSuspension.getLinearSensorInfo();
      screen.printSuspension(suspention);
      break;
    case (3): //
      Serial.println("Opt 3");
      break;
    default:
      screen.printHome(sat);
  }
}
