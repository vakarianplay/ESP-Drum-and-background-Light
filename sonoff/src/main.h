#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "button.h"
#include "uptime_formatter.h"

WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

button btn1(0);
