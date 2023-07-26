
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

class Screen
{
private:
  int flag = 10;

  int SCREEN_WIDTH = 128;    // OLED display width, in pixels
  int SCREEN_HEIGHT = 32;    // OLED display height, in pixels
  int8_t OLED_RESET = -1;    // Reset pin # (or -1 if sharing Arduino reset pin)
  int SCREEN_ADDRESS = 0x3C; ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
  Adafruit_SH1106 display;

public:
  void init()
  {
    // Iniciando Pantalla
    display.begin(SH1106_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
    display.setTextSize(3); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("Sebas84");

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("v 1.0");
    display.display(); // Show initial text
    delay(1000);
  }
  Screen()
      : display(OLED_RESET)
  {
    // this->init();
  }

  void printScreen()
  {
    // display.clearDisplay();
    printHeader();
    display.display(); // Show initial text
  }
  void printTime(String text)
  {
    // display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(text);
  }
  void printSuspension(String text)
  {
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Suspension");

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(15, 35);
    display.println(text);

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");
    display.display(); // Show initial text
  }
  void printGPS(String sat, String log, String lat)
  {

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 55);
    display.println(sat);
  }
  void printHeader()
  {
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(85, 56);
    display.println("Sebas84");
  }
  void printHome(int sat)
  {
    display.clearDisplay();
    display.setTextSize(3); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("Sebas84");

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 55);
    if (sat == -1)
    {
      display.println("Verifique el GPS.");
    }
    else
    {
      if (sat == -2)
      {
        display.println("Buscando Satelite");
      }
      else
      {
        display.print("Sat ");
        display.println(sat);
      }
    }
    display.display(); // Show initial text
  }
  void clearScreen()
  {
    display.clearDisplay();
  }
  /**
   * @brief Laps, time, satellites,
   * 
   * @param time 
   * @param text 
   */
  void printLaptimer(String time, String sat,float speed,String laps)
  {
    display.clearDisplay();

    display.setTextSize(3); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(time);
    display.setTextSize(1); // Draw 2X-scale text
    

    display.setCursor(0, 30);
    display.print(laps);

    display.setCursor(70, 40);
    display.print(speed);
    display.print(" km/h");

    display.drawLine(0, 50, display.width()-1,  50, WHITE);
    display.setCursor(0, 55);
    display.print("Sat: ");
    display.print(sat);
    display.print("   Laps: ");
    display.print("0");
    display.display(); // Show initial text
  }
};