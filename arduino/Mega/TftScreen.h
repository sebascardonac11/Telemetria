#include "HardwareSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>


/**
This class is develop to a 1.8 TFT SPI 128x160 v1.1 screen with controller ST7735S
*/
class TftScreen {
  // 'logo-icon', 128x169px
private:
  int flag = 10;
  String opt = "";

  // pin definition for the Uno
  int8_t cs = 30;
  int8_t dc = 29;
  int8_t rst = 31;

  Adafruit_ST7735 tft;
public:

  TftScreen()
    : tft(cs, dc, rst) {
    // this->init();
  }

  void init() {
    this->opt = "init";
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextWrap(false);
    tft.setRotation(135);

    tft.setCursor(10, 10);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(3);
    tft.print("Sebas84");

    tft.setCursor(120, 100);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("v1.0");
  }
  /**
   * @brief ...
   * @param sat 
   * @param text 
   */
  void printHome(int sat, float hours, String text) {
    if (this->opt != "printHome") {
      this->opt = "printHome";
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ST7735_WHITE);
      tft.setTextSize(3);
      tft.print("Sebas84");
    }
    tft.setCursor(10, 50);
    tft.setTextSize(1);
    if (sat == -1) {
      tft.print("Verifique el GPS.");
    } else {
      if (sat == -2) {
        tft.print("Buscando Satelite");
      } else {
        tft.print(sat);
      }
    }
    tft.setCursor(10, 115);
    tft.print(text);
    tft.setCursor(90, 115);
    tft.print("horas:");
    tft.setCursor(130, 115);
    tft.print(hours);
  }
  /**
   * @brief Laps, time, satellites,
   * 
   * @param time 
   * @param text 
   */
  void printLaptimer(String time, String sat, float speed, String laps, String track, float hours,String date, String text) {
    if (this->opt != "printLaptimer") {
      this->opt = "printLaptimer";

      tft.fillScreen(ST77XX_BLACK);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setCursor(0, 0);
      tft.print("Sat: ");
      tft.setCursor(50, 0);
      tft.print("Circuito");
      tft.setCursor(120, 0);
      tft.print(date);
      tft.setCursor(10, 60);
      tft.print("Velocidad: ");
      tft.setCursor(100, 60);
      tft.print("Vueltas: ");
      tft.setCursor(10, 115);
      tft.print("Info: ");
    }
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setCursor(10, 25);
    tft.setTextSize(3);
    tft.print(time);


    tft.drawRect(100, 70, 50, 40, ST7735_WHITE);
    tft.setCursor(115, 80);
    tft.print(laps);

    tft.setCursor(10, 75);
    tft.print(speed);

    tft.drawLine(0, 15, tft.width(), 15, ST7735_WHITE);
    tft.setTextSize(1);
    tft.setCursor(25, 0);
    tft.print(sat);
    tft.setCursor(50, 0);
    tft.print(track);

    tft.setCursor(70, 115);
    tft.print(text);

    tft.setCursor(130, 115);
    tft.print(hours);
  }
  int printMenu(int selected) {
    if (this->opt != "menu") {
      this->opt = "menu";
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextSize(3);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setCursor((tft.width() / 2) - 40, 0);
      tft.print("Menu ");
      tft.setTextSize(2);
    }
    tft.setCursor(10, 30);
    tft.print("  Suspension");
    tft.setCursor(10, 50);
    tft.print("  Rpms");
    switch (selected) {
      case (0):  //Suspension
        tft.setCursor(10, 30);
        tft.print("> Suspension");
        break;
      case (1):
        tft.setCursor(10, 50);
        tft.print("> Rpms");
        break;
    }
    if (selected > 1) {
      return -1;
    } else {
      return selected;
    }
  }
  void printText(String text) {
    if (this->opt != "printText") {
      this->opt = "printText";

      tft.fillScreen(ST77XX_BLACK);
    }
    tft.setCursor(100, 100);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setTextSize(2);
    tft.print(text);
  }
  void printSuspension(String front, String rear) {
    if (this->opt != "printSuspension") {
      this->opt = "printSuspension";

      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setTextSize(2);
      tft.print("Suspension");
    }

    tft.setCursor(100, 100);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setTextSize(2);
    tft.print(front);
  }
  void printGPS(String sat, String log, String lat) {
  }
  void printRPMS(String rpm) {
    if (this->opt != "printRPMS") {
     // this->flag = 0;
      this->opt = "printRPMS";

      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setTextSize(3);
      tft.print("RPMS");
    }
   // this->flag++;

    tft.setCursor(100, 100);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setTextSize(2);
    tft.print(rpm);
  }
  void printLastLap(String time, int lap) {
    if (this->opt != "printLastLap") {
      this->opt = "printLastLap";
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setTextSize(2);
      tft.print("Resumen");
    }

    tft.setCursor(10, 60);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setTextSize(2);
    tft.print(time);
     tft.setCursor(10, 100);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setTextSize(2);
    tft.print(lap);
  }
  void printSession() {
  }
};