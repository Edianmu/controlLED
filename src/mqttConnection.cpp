#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* mqttClient = "****"; //IP
const char* mqttPub = "****"; //Topic

const int buttonLed = 0;
const int ledPin = LED_BUILTIN; 

int val = 0; 
int oldVal = 0; 
int str = 0; 

WiFiClient espclient;
PubSubClient client(espclient);

void reconnect(){

client.setServer(mqttClient, 1883);
pinMode(buttonLed, INPUT_PULLUP);
pinMode(ledPin, OUTPUT);

  while (!client.connected())
  {
    Serial.print("Intentando establecer conexión MQTT... ");
    String clientId = "ESP8266_Edisson";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("Conectado");
      if (client.subscribe(mqttPub))
      {
        Serial.printf("El cliente %s está conectado a Mosquitto MQTT \n", clientId.c_str());
      }
      else{
        Serial.print("Falló suscripción ");
        Serial.print(client.state());
        Serial.print("Intentando reconectar en 5 segundos");
        delay(5000);
      } 
    }
  }   
}

void messagePub() {
  if(!client.connected()){
    reconnect();
  }

  if(client.connected()){
    
    val= digitalRead(buttonLed); 
    
    if ((val == HIGH) && (oldVal == LOW))
    {
    str= 1 - str;
    delay(10);
    }

    oldVal = val; 

    if (str == 0)
    {
      client.publish(mqttPub, "on");
      digitalWrite(ledPin, 0);
      delay(300);
    }
    else
    {
      client.publish(mqttPub, "off");
      digitalWrite(ledPin, 1); 
      delay(300);
    }
  }
  client.loop();
}

void loopConnection(){
  client.loop();
}