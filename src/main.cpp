#include "ntust_login.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
const char *ssid = "NTUST-UAM";

void setup() {
  Serial.begin(115200);
  Serial.println("ESP8266 Start");
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if(login("test","test"))
    Serial.println("Login OK");
  else
    Serial.println("Login Failed");

}

void loop() {

}
