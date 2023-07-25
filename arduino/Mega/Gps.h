#include "WString.h"
/**
 */
#include <SoftwareSerial.h>
#include <TinyGPS.h>

class Gps {
private:
  // Pines Para mega es (10,9), Micro (9,8)
  byte txPin = 10;
  byte rxPin = 9;
  SoftwareSerial ss;
  TinyGPS gps;
  float flat, flon;
  int sat = -1;

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
  int sincroSatellites() {

    bool newData = false;
    

    unsigned long chars;
    unsigned short sentences, failed;
    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;) {
      while (ss.available()) {
        char c = ss.read();
        // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c))  // Did a new valid sentence come in?
          newData = true;
      }
    }
    gps.stats(&chars, &sentences, &failed);
    //Serial.println(chars);
    if (chars != 0){
      sat = 0;
    }
    if (newData) {    
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      float distance = TinyGPS::distance_between(flat, flon, 6.151369, -15.605492);
      sat = gps.satellites();
    }
    return sat;
  }
  /**
     */
  String getLocation() {

    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
    String res = "";

    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;) {
      while (ss.available()) {
        char c = ss.read();
        // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c))  // Did a new valid sentence come in?
          newData = true;
      }
    }

    if (newData) {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      Serial.print(F("LAT="));
      Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Serial.print(F(" LON="));
      Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print(F(" SAT="));
      Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      Serial.print(F(" PREC="));
      float distance = TinyGPS::distance_between(flat, flon, 6.151369, -15.605492);
      Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
      res += "Sat:";
      res += gps.satellites();
      res += "|Lat: ";
      res += String(flat, 6);
      res += ",Long: ";
      res += String(flon, 6);
      res += "Dis a Sala";
      res += String(distance, 6);
    } else {
      res += "Buscando GPS";
    }

    gps.stats(&chars, &sentences, &failed);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" CHARS=");
    Serial.print(chars);
    Serial.print(" SENTENCES=");
    Serial.print(sentences);
    Serial.print(" CSUM ERR=");
    Serial.println(failed);
    if (chars == 0) {
      Serial.println("** No characters received from GPS: check wiring **");
      res += "         Verifique modulo GPS. ";
    }
    return res;
  }
  float getLatitude(){
    return this->flat;
  }

  float getLongitude(){
    return this->flon;
  }
  int getSatellite(){
    return this->sat;
  }
  float getDistance(float lat, float lon){
    return TinyGPS::distance_between(this->flat, this->flon, lat, lon);
  }
};