class Track {
private:
  String name;
  float startLong, startLat;
  float endLong, endLat;
  int width;

public:
  Track(String name, float startLong, float startLat, float endLong, float endLat, int width) {
    this->name = name;
    this->startLong = startLong;
    this->endLong = endLong;
    this->startLat = startLat;
    this->endLat = endLat;
    this->width = width;
  }
  
};