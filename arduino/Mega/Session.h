#include "WString.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "Lap.h"

class Session {
private:
  char fecha[20];
  String trackName;
  Lap *laps[50];
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
    this->laps[this->lap] = new Lap(
      (startLap - this->lastLap),
      this->lastLap,
      startLap,
      printTime((startLap - this->lastLap)));

    this->lap++;
    this->lastLap = startLap - this->startLap;
    this->startLap = startLap;
  }
  int getLap() {
    return this->lap;
  }
  String getLasLap() {
    return this->printTime((this->startLap - this->lastLap));
  }
  String getTime() {
    if (this->lap == 0)
      return "0:00:00";
    else
      return this->printTime((millis() - this->startLap));
  }
  void setTrackName(String track){
    this->trackName = track;
  }
  /**

*/
  String printTime(long startTime) {
    String Time = "0:00:00";
    if (startTime != 0) {
      int centesimos = 0;
      double diff = startTime;
      diff = diff / 3600000;
      int hour = diff;
      diff = (diff - hour) * 60;
      int min = diff;
      diff = (diff - min) * 60;
      int sec = diff;
      diff = (diff - sec) * 1000;
      Time = min;
      Time += (":");
      Time += (sec);
      Time += (":");
      Time += diff;
    }

    return (Time.substring(0, 7));
  }
  String getSummary() {
    String text = "";
    for (int i = 0; i < this->lap; i++) {
      text += this->laps[i]->getPrintTime();
      text += " , ";
    }
    return text;
  }
};
