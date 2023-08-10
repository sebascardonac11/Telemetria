#include "Arduino.h"
#include "Lap.h"

class Session {
private:
  char fecha[20];
  String trackName;
  int lap = 0;
  String Time = "0:00:00";
  int minutos = 0;
  long startLap;

public:
  Session(String trackName) {
    this->trackName = trackName;
    this->startLap= millis();
  }

  void addLap(long startLap) {
    this->lap++;
    this->startLap = startLap;
  }
  int getLap() {
    return this->lap;
  }
  String getTime() {
    this->lapTimer();
    return this->Time.substring(0, 7);
  }
  /**

*/
  String lapTimer() {
    if (this->lap > 0) {
      int segundos = 0;
      long diff = (millis() - this->startLap);
      int centesimos = 0;

      segundos = (diff / 1000);
      centesimos = (diff - (segundos * 1000));
      segundos = segundos - (minutos * 60);
      if (segundos >= 60) {
        segundos = 0;
        minutos++;
      }
      this->Time = (minutos);
      this->Time += (":");
      this->Time += (segundos);
      this->Time += (":");
      this->Time += String(centesimos,2);
/*
      Serial.print(this->Time);
      Serial.print(".           diff ");
      Serial.print(diff);
      Serial.print(".           Inicial ");
      Serial.println(this->startLap);*/
    }
    return (this->Time.substring(0, 7));
  }
};