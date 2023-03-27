#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include "uptime_formatter.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"

// const char* ssid = "SSID";
// const char* password = "password";

// IPAddress ip(192, 168, 1, 253);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

float Temperature;
float Humidity;

const float TempCoeff = 2.1;
const float HumCoeff = 5.7;
