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
  float flat, flon, speed;
  int sat = -1;
  char date[32];

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
    unsigned short sentences, failed;
    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 100;) {
      while (ss.available()) {
        char c = ss.read();
        // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c))  // Did a new valid sentence come in?
          newData = true;
      }
    }
    gps.stats(&chars, &sentences, &failed);
    //Serial.println(chars);
    if (chars != 0) {
      sat = -2;
    }
    if (newData) {
      unsigned long age;
      int year;

      byte month, day, hour, minute, second, hundredths;
      gps.f_get_position(&flat, &flon, &age);
      sat = gps.satellites();
      this->speed = gps.f_speed_kmph();
      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
      sprintf(this->date, "%02d/%02d/%02d %02d:%02d:%02d   ",
              month, day, year, hour, minute, second);
    }
    return sat;
  }

  float getLatitude() {
    return this->flat;
  }
  char getDate() {
    return this->date;
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
  float getDistance(float lat, float lon) {
    if (this->sat >= 0)
      return TinyGPS::distance_between(this->flat, this->flon, lat, lon);
    else
      return 0.0;
  }
};