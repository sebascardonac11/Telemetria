#include "WString.h"
#include "HardwareSerial.h"
/**
 */
#include <SoftwareSerial.h>

#include "TinyGPS++.h"

class Gps {
private:
  // Pines Para mega es (10,9), Micro (9,8)
  byte txPin = 10;
  byte rxPin = 9;
  SoftwareSerial ss;
  TinyGPSPlus gps;
  float flat, flon, speed;
  int sat = -2;
  char date[32] = "00000000000000000000000000000000";
  String date2 = "";

  void init() {
    this->ss.begin(9600);
  }

public:
  Gps(byte txPin, byte rxPin)
    : ss(txPin, rxPin) {
    this->txPin = txPin;
    this->rxPin = rxPin;
    this->init();
  }
  Gps()
    : ss(this->txPin, this->rxPin) {
    this->init();
  }
  /**
  * This function connect the device with the satellites and asign the values of the class.
  */
  int readGps() {
    bool newData = false;
    unsigned long chars;
    // For one second we parse GPS data and report some key values
    //for (unsigned long start = millis(); millis() - start < 500;) {
      while (ss.available()) {
        char c = ss.read();
        //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c)) {  // Did a new valid sentence come in?
          //Serial.println(gps.charsProcessed());
          if (gps.location.isValid()) {
            newData = true;
            //Serial.println("Datos encontrados");
          }
        }
      }
    //}
    if (gps.charsProcessed() < 10) {
      Serial.println(F("No GPS detected: check wiring."));
      sat = -1;
    }
    if (newData) {
      unsigned long age;
      int year;

      byte month, day, hour, minute, second, hundredths;
      this->flat = gps.location.lat();
      this->flon = gps.location.lng();

      //Serial.println(String(this->flat,6));

      //Serial.println(String(this->flon,6));
      this->sat = gps.satellites.value();
      this->speed = gps.speed.kmph();
      sprintf(this->date, "%02d/%02d/%02d %02d:%02d:%02d   ",
              gps.date.month(), gps.date.day(), gps.date.year(), gps.time.hour(), gps.time.minute(), gps.time.second());
      //      Serial.println(this->date);

      this->date2 = this->date;
    }
    return sat;
  }

  float getLatitude() {
    return this->flat;
  }
  String getDate() {
    return this->date2;
  }
  float getLongitude() {
    return this->flon;
  }
  float getSpeed() {
    return this->speed;
  }
  int getSatellite() {
    return this->sat;
  }
  /**
  * Distance in meters
  */
  float getDistance(float lon,float lat) {
    if (this->sat >= 0){
      double distance=TinyGPSPlus::distanceBetween(
        this->flat, this->flon,
        lat, lon);
      return distance;
    }else
      return 0.0;
  }
};