class Track {
private:
  String name;
  float startLong, startLat;
  float endLong, endLat;
  float width;

public:
  Track() {
  }
  Track(String name, float startLong, float startLat, int width) {
    this->name = name;
    this->startLong = startLong;
    this->startLat = startLat;
    this->width = width;
  }
  /**/
  String getName() {
    return this->name;
  }
  /**/
  float getWidth() {
    return this->width;
  }
  /**/
  float getStartLong() {
    return this->startLong;
  }
  /**/
  float getStartLat() {
    return this->startLat;
  }
};