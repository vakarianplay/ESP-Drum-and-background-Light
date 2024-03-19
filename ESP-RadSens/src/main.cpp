
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HTTPUpdateServer.h>
#include "radinterface.h"
#include "index.h"
#include "uptime_formatter.h"

enum RAD {STAT, DYN, IMP};

unsigned long previousMillis = 0;
const unsigned long interval = 500;
// const char* ssid = "MUTINY";
// const char* password = "816planet";
const char* ssid = "ESPRadSens";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);


HTTPUpdateServer httpUpdater;
WebServer server(80);
RadInterface radInterface(5, 4, 105);
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void handleRoot()
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void sensorRead(uint8_t id)
{
  if (id == RAD::STAT) {
    server.send(200, "text/plane", radInterface.getStatString());
  }
  if (id == RAD::DYN) {
    server.send(200, "text/plane", radInterface.getDynString());
  }
  if (id == RAD::IMP) {
    server.send(200, "text/plane", radInterface.getImpString());
  }
}

void uptime() {
    server.send(200, "text/plane", uptime_formatter::getUptime());
}

void jsonProcessor() {
  String json = "{";
    json += "\"Rad Stat\": " + radInterface.getStatString() + ",";
    json += "\"Rad Dyn\": " + radInterface.getDynString() + ",";
    json += "\"Imp\": " + radInterface.getImpString();
    json += "}";
    server.send(200, "application/json", json);
}

void setup()
{
  Serial.begin(9600);
  // WiFi.begin(ssid, password);

  WiFi.softAPConfig(local_ip, gateway, subnet); //Create AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  server.on("/", handleRoot);
  // server.on("/handleReset", handleReset);
  server.on("/readStat", [&]() {sensorRead(RAD::STAT);});
  server.on("/readDyn", [&]() {sensorRead(RAD::DYN);});
  server.on("/readImp", [&]() {sensorRead(RAD::IMP);});
  server.on("/readUptime", uptime);
  server.on("/data", HTTP_GET, jsonProcessor);

  httpUpdater.setup(&server, "/firmware");

  server.begin();

  oled.init(5, 4);
  oled.flipV(1);
  oled.flipH(1);
  oled.clear();
  oled.setScale(2);
  oled.print("CG_RadSens");
  oled.setCursor(0, 5);
  delay(1000);
  oled.clear();
}

void loop()
{
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    radInterface.tick();
  }
}
