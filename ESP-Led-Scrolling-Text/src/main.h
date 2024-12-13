#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Preferences.h>
#include "datagrabber.h"
#include <Arduino.h>

const char* ssid = "roof";
const char* password = "12345618";

unsigned long previousMillis = 0;
const long interval = 3000; 

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80);
Preferences preferences;
DataGrabber dataGrabber;

// WiFiClient client;
// HTTPClient http;


const char webpage[] PROGMEM = R"=====(
<!DOCTYPE HTML><html>
<head>
<title>ESP Settings</title>
 <meta charset="utf-8" name="viewport" content="width=device-width initial-scale=1">
</head>
<body>
<h1>ESP MAX7219_Led_Scrolling_Text</h1>
<form method="POST" action="/save">
  Streaming Url: <input type="text" name="streamingUrl" id="streamingUrl" value="%s"><br>
  Scrolling Speed: <input type="number" name="scrollingSpeed" id="scrollingSpeed" value="%d"><br>
  <input type="submit" value="💾 Save and reboot">
</form>
</body>
</html>


)=====";