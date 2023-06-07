#include <ESP8266WiFi.h>

/**
* This function connect to wifi.
*/
bool connectWifi(String ssid, String password, String ssid2, String password2) {
  bool isConnect= wifiConnect(ssid, password);
  if (!isConnect) {  //No se conectó
    isConnect=wifiConnect(ssid2, password2);
  }
  return isConnect;
}

bool wifiConnect(String ssid, String password) {
  Serial.println("Connecting with ");
  Serial.print(ssid);
  Serial.print(" ");
  byte cont = 0;
  byte led = 0;
  byte max_intentos = 10;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {  //Cuenta hasta 50 si no se puede conectar lo cancela
    if (led == 0) {
      digitalWrite(ledWifi, LOW);  //ON
      led = 1;
    } else {
      digitalWrite(ledWifi, HIGH);  //ON
    }
    cont++;
    delay(500);
    Serial.print(".");
    Serial.print(cont);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("*********************************************");
    digitalWrite(ledWifi, LOW);  //ON
    digitalWrite(redLed, HIGH);  //OFF
    return true;
  } else {
    digitalWrite(redLed, LOW);  //OFF
    return false;
  }
}
/**
*
*/
String getInfoConnect(){
  String res = "{";
    res +=   "\"localIp\":\""+ WiFi.localIP().toString()+"\"";
    res += ",\"macAdress\":\"" + WiFi.macAddress() + "\"";
    res += ",\"SSID\":\"" + WiFi.SSID() + "\"";
    res += "}";
    return res;
}