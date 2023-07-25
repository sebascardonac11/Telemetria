#include <SD.h>
#include <SPI.h>

#define CS_PIN 53 

File file;

void beginSD() {
  Serial.println("Initializing SD card...");

  if (SD.begin(CS_PIN)) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }
}
int createFile(char filename[]) {
  file = SD.open(filename, FILE_WRITE);

  if (file) {
    Serial.println("File created successfully.");
    return 1;
  } else {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[]) {
  if (file) {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile() {
  if (file) {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[]) {
  file = SD.open(filename);
  if (file) {
    Serial.println("File opened with success!");
    return 1;
  } else {
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine() {
  String received = "";
  char ch;
  while (file.available()) {
    ch = file.read();
    if (ch == '\n') {
      return String(received);
    } else {
      received += ch;
    }
  }
  return "";
}
