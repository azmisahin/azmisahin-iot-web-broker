#include "ESP8266WiFi.h"
#include <MQTTClient.h>

char* ssid = "TT-automation";
char* ssid_password = "12345678";
char* brokerAddress = "192.168.1.28"; //"broker.shiftr.io";
char* automationUser = "8ac98f73";
char* automationScret = "7ae7c0ecf6148c3a";
char* channelName = "iot";
char* channelTopic = "iot-sensor";

WiFiClient WiFiclient;
MQTTClient client;
 
unsigned long lastMillis = 0;

void setup() {
 Serial.begin(115200);
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, ssid_password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 
 Serial.println("");
 Serial.println("WiFi connected");  
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 delay(2000);
 
 Serial.print("connecting to MQTT broker...");
 client.begin(brokerAddress, WiFiclient);
 connect();
}
 
void connect() {
 while (!client.connect(channelName, automationUser, automationScret)) {
   Serial.print(".");
 }
 
 Serial.println("\nconnected!");
 client.subscribe(channelTopic);
}
 
void loop() {
 int val = analogRead(A0);
 client.loop();
 if(!client.connected()) {
   connect();
 }
 
 if(millis() - lastMillis > 1000) {
   lastMillis = millis();
   client.publish(channelTopic, (String)val);
 }
}
