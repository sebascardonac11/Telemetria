#include <Arduino.h>
#include <TimeLib.h>
#include "Test.h"
#include "Screen.h"

float valMin = 50.0;
float valMax = 1024.0;


unsigned int Imilisegundos;
int minutos = 0;

/* Prototypes */
void beginScreen();  // External function screem.ino
void printSuspension(String text);
void printTime(String text);
void printScreen();  // External function screem.ino
void clearScreen();

void beginGps();
String getLocation();

void beginSD();
test t;
Screen screen;
void setup() {

//  test t = new test();

  // Inicia Serial
  pinMode(53 , OUTPUT);
  Serial.begin(115200);

  beginScreen();
  beginGps();
  beginSD();
  setTime(12, 39, 50, 18, 07, 2023);
  Imilisegundos = millis();
}

void loop() {
  clearScreen();
  float distance = getLinearSensorInfo();
  /* String res = "{\"Fecha\":\"";
  res += getTimestamp();
  res += "\",\"distance\":";
  res += distance;
  res += "}";
  //Serial.println(res);
*/
  printTime(cronometro(Imilisegundos));
  printSuspension(getLocation());

  printScreen();
}


/**
* In this function is calcultation the linear sensors.
*/
float getLinearSensorInfo() {
  int pinInCC = analogRead(A0);
  float distance = 0;
  distance = (pinInCC - valMax) * (70.0) / (valMax - valMin);
  distance = distance * -1;

  return distance;
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

/**

*/
String cronometro(int Imillis) {

  int segundos = 0;
  long diff=(millis() - Imillis);
  int centesimos = 0;
  String lapTimer = "0:00:000";
  segundos = (diff / 1000);
  centesimos = (diff - (segundos * 1000));
  segundos = segundos - (minutos * 60);
  if (segundos >= 60) {
    segundos = 0;
    minutos++;
  }

  if (minutos >= 60) {
    minutos = 0;
    Imilisegundos = millis();
  }


  lapTimer = (minutos);
  lapTimer += (":");
  lapTimer += (segundos);
  lapTimer += (":");
  lapTimer += (centesimos);
/*
  Serial.print(lapTimer);

  Serial.print(".           diff ");
  Serial.print(diff);
  Serial.print(".           Inicial ");
  Serial.println(Imillis);*/
  return (lapTimer.substring(0, 7));
}

/*
LAT, LONG
5.032358, -75.478159 Inicio recta

5.032286, -75.478699 meta
5.032240, -75.478686 Meta

5.032193, -75.479048 Final recta


5.033210, -75.479752 Salida curva fondo
*/