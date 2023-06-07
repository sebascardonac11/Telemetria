#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>

#define ledWifi D4  //Led Azul de la placa
#define redLed 16   // Led Rojo de la placa

float valMin = 50.0;
float valMax = 1024.0;

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80);  //Server on port 80
//Your Domain name with URL path or IP address with path
const char* serverName = "https://49g31zaftb.execute-api.us-west-2.amazonaws.com/dev";
/* Prototypes */
bool connectWifi(String ssid, String password, String ssid2, String password2);  // funcion externa en wifi.ino
String getInfoConnect();                                                         // funcion externa en wifi.ino

void setup() {
  // Inicia Serial
  pinMode(ledWifi, OUTPUT);  //Led Azul de la placa
  pinMode(redLed, OUTPUT);   // Led rojo de la placa
  Serial.begin(115200);

  if (connectWifi("Daytona84", "Calima175", "Sebascardonac11", "Daytona123")) {
    String info = sendInfo(getInfoConnect());
    Serial.println(info);
    //hh:mm:ss:dd:mm:aaaa
    setTime(19, 20, 50, 04, 05, 2023);
    server.enableCORS(true);
    server.on("/linearSensor", getSensorServer);
    server.begin();  //Start server
    Serial.println("HTTP server started");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    //sendInfo();
    server.handleClient();  //Handle client requests
  } else {
  }
}


/**
* In this function is calcultation the linear sensors.
*/
float getLinearSensorInfo() {
  int pinInCC = analogRead(A0);
  float distance = 0;
  distance = (pinInCC - valMax) * (70.0) / (valMax - valMin);
  distance = distance * -1;
  Serial.print("Resistence : ");
  Serial.println(pinInCC);
  return distance;
}

/***
* handler of server.
*/
void getSensorServer() {

  float distance = getLinearSensorInfo();
  String res = "{\"Timestamp\":\"";
  res += getTimestamp();
  res += "\",\"distance\":";
  res += distance;
  res += "}";
  Serial.println(res);
  server.send(200, "text/json", res);  //Send ADC value only
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

String sendInfo(String httpRequestData) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  //WiFiClient client;
  HTTPClient http;
  if (http.begin(*client, serverName)) {
    http.addHeader("Content-Type", "application/json");
    Serial.println(httpRequestData);
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      return http.getString();
    }else{
      Serial.print(httpResponseCode);
      Serial.println(" Unable to connect with AWS");
      return "null";
    }
  } else {
    Serial.println("Unable to connect with AWS");
    return "null";
  }
  // Free resources
  http.end();
}
