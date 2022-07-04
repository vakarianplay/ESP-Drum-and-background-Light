#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

const int relayPin = 12;
const int ledPin = 13;
