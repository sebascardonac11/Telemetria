class Lap {
private:
  long time;
  long startTime;
  long endTime;
  String printTime;

public:
  Lap(long time, long startTime, long endTime,String printTime) {
    this->startTime = startTime;
    this->endTime = endTime;
    this->time = time;
    this->printTime = printTime;
  }

  String getPrintTime() {
    return this->printTime;
  }
};