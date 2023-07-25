#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>


#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
//#define OLED_RESET 1;       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Screen {
  Adafruit_SH1106 display();
private:
  
  int flag = 10;
public:
  int getFlag() {
    return flag;
  }

  void beginScreen() {
    // Iniciando Pantalla

    //display.begin(SH1106_SWITCHCAPVCC, SCREEN_ADDRESS);
   /* display.clearDisplay();
    display.setTextSize(3);  // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("Sebas84");
    display.display();  // Show initial text
    delay(1000);*/
  }
 
};