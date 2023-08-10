
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

class Screen {
private:
  int flag = 10;

  int SCREEN_WIDTH = 128;     // OLED display width, in pixels
  int SCREEN_HEIGHT = 32;     // OLED display height, in pixels
  int8_t OLED_RESET = -1;     // Reset pin # (or -1 if sharing Arduino reset pin)
  int SCREEN_ADDRESS = 0x3C;  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
  Adafruit_SH1106 display;
  long lastScreenRefresh = 0;

public:
  void init() {
    // Iniciando Pantalla
    display.begin(SH1106_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
    display.setTextSize(3);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("Sebas84");

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("v 1.0");
    display.display();  // Show initial text
    //delay(1000);
  }
  Screen()
    : display(OLED_RESET) {
    // this->init();
  }
  void printMenu(int selected) {
    // Serial.println(selected);
    if ((millis() - lastScreenRefresh) > 500) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(22, 0);
      display.print("Sebas84");
      display.drawLine(0, 9, 128, 9, WHITE);

      display.setCursor(0, 11);
      if (selected == 0) display.print(" >");
      display.print(" CONFIGURACION");

      display.setCursor(0, 20);
      if (selected == 1) display.print(" >");
      display.print(" SUSPENSION");

      display.setCursor(0, 29);
      if (selected == 2) display.print(" >");
      display.print(" RPMS");

      display.setCursor(0, 47);
      if (selected == 3) display.print(" >");
      display.print(" HOROMETRO");
      display.setCursor(0, 56);
      if (selected == 4) display.print(" >");
      display.print(" GPSs");
      display.display();  // Show initial text
      lastScreenRefresh = millis();
    }
  }
  void printText(String text) {
    display.clearDisplay();
    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(text);
    display.display();  // Show initial text
  }
  void printSuspension(String text) {
    display.clearDisplay();
    display.setTextSize(2);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Suspension");

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(15, 35);
    display.println(text);

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");
    display.display();  // Show initial text
  }
  void printGPS(String sat, String log, String lat) {

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 55);
    display.println(sat);
  }
  void printRPMS(String rpm) {
    display.clearDisplay();
    display.setTextSize(2);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor((display.width() / 2) - 10, 10);
    display.print("RPM");

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(1, 35);
    display.print(rpm);

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");
    display.display();  // Show initial text
  }
  void printHeader() {
    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");
  }
  void printHome(int sat, String date) {
    display.clearDisplay();
    display.setTextSize(3);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("Sebas84");

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(date);

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 55);
    if (sat == -1) {
      display.println("Verifique el GPS.");
    } else {
      if (sat == -2) {
        display.println("Buscando Satelite");
      } else {
        display.print("Sat ");
        display.println(sat);
      }
    }
    display.display();  // Show initial text
  }
  /**
   * @brief Laps, time, satellites,
   * 
   * @param time 
   * @param text 
   */
  void printLaptimer(String time, String sat, float speed, String laps, String date) {
    display.clearDisplay();

    display.setTextSize(3);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(time);
    display.setTextSize(1);  // Draw 2X-scale text


    display.setCursor(0, 30);
    display.print(date);

    display.setCursor(70, 40);
    display.print(speed);
    display.print("km/h");

    display.drawLine(0, 50, display.width() - 1, 50, WHITE);
    display.setCursor(0, 55);
    display.print("Sat: ");
    display.print(sat);
    display.print("   Laps: ");
    display.print(laps);
    display.display();  // Show initial text
  }
  void printLastLap(String time, int lap) {
    display.clearDisplay();

    display.setTextSize(3);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(time);
    display.setTextSize(1);  // Draw 2X-scale text

    display.setCursor(0, 55);
    display.print("   Laps: ");
    display.print(lap);

    display.setTextSize(1);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");

    display.display();  // Show initial text
  }
};