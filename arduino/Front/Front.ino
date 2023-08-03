#include <Arduino.h>

#include <TimeLib.h>
#include "Screen.h"

int minutos = 0;

/* Prototypes */

Screen screen;
void setup() {

  // Inicia Serial
  pinMode(53, OUTPUT);
  Serial.begin(115200);
  screen.init();

  setTime(12, 39, 50, 18, 07, 2023);
}

void loop() {
  Serial.println("Loop");
  screen.printLaptimer("0:00:00", "5", 160.5, "9");
  delay(1000);
}
/*
FUNCION PARA OBTENER LA FECHA EN MODO TEXTO
Devuelve: DD-MM-AAAA HH:MM:SS
*/
String getTimestamp() {

  char fecha[20];
  time_t time = now();

  int dia = day();
  int mes = month();
  int anio = year();
  int hora = hour();
  int minuto = minute();
  int segundo = second();

  sprintf(fecha, "%.2d.%.2d.%.4d %.2d:%.2d:%.2d", dia, mes, anio, hora, minuto, segundo);
  return String(fecha);
}
