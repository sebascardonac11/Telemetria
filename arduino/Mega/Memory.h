#include <EEPROM.h>


/**
* This class have the responsability to save the data in EEPROM Memory
|Address  | Description |
|  0      | Date        |
| 10      | Hour        |
*/
class Memory {
private:
  int i;
  EEPROMClass memory;

public:

  /**
* Return the date saved in the address 0.
*/
  String getDate() {
    String date;
    this->memory.get(0, date);
    return date;
  }

  /**
* Return the date saved in the address 0.
*/
  float getHour() {
    float hour;
    this->memory.get(10, hour);
    return hour;
  }
  /**
* This fuction put the hour of the engine is ON.
*/
  void setHour(float hour) {
    this->memory.put(10, hour);
  }
};