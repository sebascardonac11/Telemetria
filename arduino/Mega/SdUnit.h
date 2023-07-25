#include <SD.h>
#include <SPI.h>

class SdUnit {
private:
  int CS_PIN = 53;

public:
  SdUnit() {
  }
  void init() {
   // Serial.print("Initializing SD card... in pin ");
   // Serial.println(CS_PIN);
    
    if (SD.begin(CS_PIN)) {
      Serial.println("SD card is ready to use.");
    } else {
      Serial.println("SD card initialization failed");
    }
  }
};