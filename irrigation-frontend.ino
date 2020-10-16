#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char *ssid =  "WiFi Name";     // Enter your WiFi Name
const char *pass =  "Password"; // Enter your WiFi Password

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "User Name"
#define MQTT_PASS "AIO Key"

Adafruit_MQTT_Publish AgricultureData = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/AgricultureData"); //publishing feed setup
Adafruit_MQTT_Subscribe LED = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/LED");
Adafruit_MQTT_Subscribe Pump = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Pump"); //subscribed feed setup

int ldrStatus = analogRead(ldrPin);  //LDR reading
if (ldrStatus <= 200) {
    digitalWrite(ledPin, HIGH);
} 
else {
   digitalWrite(ledPin, LOW);
}

moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) ); //read and publish moisture sensor data   
Serial.print(moisturePercentage);
Serial.println("%");
  }
if (moisturePercentage < 50) {
  digitalWrite(motorPin, HIGH);         // tun on motor
}
if (moisturePercentage > 50 && moisturePercentage < 55) {
  digitalWrite(motorPin, HIGH);        //turn on motor pump
}
if (moisturePercentage > 56) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}
if (! AgricultureData.publish(moisturePercentage)) {                    
  delay(5000);  
}
