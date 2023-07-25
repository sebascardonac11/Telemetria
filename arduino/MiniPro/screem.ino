/***************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SH1106 display(OLED_RESET);
/***************************************/

void beginScreen() {
  // Iniciando Pantalla

  display.begin(SH1106_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(3);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("Sebas84");
  display.display();  // Show initial text
  delay(1000);
}
void printScreen() {
  //display.clearDisplay();
  printHeader();
  display.display();  // Show initial text
}
void printTime(String text) {
  //display.clearDisplay();
  display.setTextSize(3);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(text);
}
void printSuspension(String text) {
  //display.clearDisplay();
  display.setTextSize(1);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 35);
  display.println(text);

  //display.display();  // Show initial text
}
void printGPS(String sat, String log, String lat) {
  
  display.setTextSize(1);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 55);
  display.println(sat);
}
void printHeader() {
  display.setTextSize(1);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(85, 56);
  display.println("Sebas84");
}

void clearScreen() {
  display.clearDisplay();
}