#include "WString.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "Lap.h"

class Session {
private:
  char fecha[20];
  String trackName;
  int lap = 0;

  int minutos = 0;
  long startLap = 0;
  long lastLap = 0;

public:
  Session(String trackName) {
    this->trackName = trackName;
    this->startLap = millis();
  }

  void addLap(long startLap) {
    this->lap++;
    this->lastLap = startLap - this->startLap;
    this->startLap = startLap;
  }
  int getLap() {
    return this->lap;
  }
  String getLasLap() {
    return this->printTime(this->lastLap, this->startLap);
  }
  String getTime() {
    return this->printTime(this->startLap, millis());
  }

  /**

*/
  String printTime(long startTime, long endTime) {
    String Time = "0:00:00";
    if (startTime != 0) {

      int centesimos = 0;
      double diff = (endTime - startTime);
      diff = diff / 3600000;
      int hour = diff;
      diff = (diff - hour  ) * 60;
      int min = diff;
      diff = (diff-min) * 60;
      int sec = diff;
      diff = (diff-sec) * 1000;
      Time = min;
      Time += (":");
      Time += (sec);
      Time += (":");
      Time += diff;
    }

    return (Time.substring(0, 7));
  }
};
