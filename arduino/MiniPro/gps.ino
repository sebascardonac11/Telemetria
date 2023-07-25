/**
*/
#include <SoftwareSerial.h>
#include <TinyGPS.h>

//Pines Para mega es (10,9), Micro (9,8)

const byte txPin = 10;
const byte rxPin = 9;


TinyGPS gps;
SoftwareSerial ss(txPin,rxPin );  //Pines Para mega es (10,9)

/**
*/
void beginGps() {
  ss.begin(9600);
}

/**
*/
String getLocation() {


  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  String res = "";

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (ss.available()) {
      char c = ss.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c))  // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print(F("LAT="));
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(F(" LON="));
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(F(" SAT="));
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(F(" PREC="));
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    res += "Sat:";
    res += gps.satellites();
    res += "|Lat: ";
    res +=  String(flat, 6);
    res += ",Long: ";
    res += String(flon,6);


  } else {
    res += "NO Satelites  ";
  }

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" SAT=");
  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0){
    Serial.println("** No characters received from GPS: check wiring **");
    res += "       Check wiring. ";
  }
  return res;
}