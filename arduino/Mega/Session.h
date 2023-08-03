#include "Lap.h"

class Session {
private:
  char fecha[20];
  String trackName;
  int lap = 0;
  String Time = "0:00:00";
  int minutos = 0;

public:
  Session(String trackName) {
    this->trackName = trackName;
  }

  void addLap(long startLap) {
    this->lap++;
  }
  String getTime() {
    return this->Time;
  }
  /**

*/
  String lapTimer(long Imillis) {
    if (this->lap > 0) {
      int segundos = 0;
      long diff = (millis() - Imillis);
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
      this->Time += (centesimos);
      /*
      Serial.print(Time);
      Serial.print(".           diff ");
      Serial.print(diff);
      Serial.print(".           Inicial ");
      Serial.println(Imillis);*/
    }
    return (this->Time.substring(0, 7));
  }
};