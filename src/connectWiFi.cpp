#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "dataWiFi.h"

void connectWiFi(){

  delay(10);
  Serial.println();
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Wifi conectado - IP: ");
  Serial.println(WiFi.localIP());
}