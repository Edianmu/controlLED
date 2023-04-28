#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "bridge.h"

void setup(){
 
  Serial.begin(115200);
  connectWiFi();
  reconnect();
}

void loop() {
 
messagePub();
loopConnection();
}