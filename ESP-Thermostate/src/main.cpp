
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "regulator.h"
#include "index.h"
#include "settingspage.h"
#include "uptime_formatter.h"

enum SENSORS {TEMP, HUM};


const uint8_t relay1 = 15;
const uint8_t relay2 = 13;
const char* ssid = "MUTINY";
const char* password = "816planet";

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80);
Regulator regulator(relay1, relay2);


void handleRoot()
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void handleSettings()
{
 String s = settingspage;
 server.send(200, "text/html", s);
}


void sensorRead(uint8_t id)
{
  if (id == SENSORS::TEMP) {
    server.send(200, "text/plane", regulator.getTempString());
  }
  if (id == SENSORS::HUM) {
    server.send(200, "text/plane", regulator.getHumString());
  }
}

void relayController(uint8_t relayNum)
{
  byte state = digitalRead(relayNum);
  digitalWrite(relayNum, !state);

  server.send(200, "text/plane", String(!state));
}

void relayStatus(uint8_t relayNum) {
    server.send(200, "text/plane", String(digitalRead(relayNum)));
}

void uptime() {
    server.send(200, "text/plane", uptime_formatter::getUptime());
}

void jsonProcessor() {
  String json = "[{";
    json += "\"Relay_1\": " + String(digitalRead(relay1)) + ",";
    json += "\"Relay_2\": " + String(digitalRead(relay2)) + ",";
    json += "\"Regulator state\": " + String(regulator.isRegulator()) + ",";
    json += "\"Sensor Temp\": " + regulator.getTempString() + ",";
    json += "\"Sensor Hum\": " + regulator.getHumString();
    json += "}, {";
    json += "\"Hysteresis\": " + regulator.getHysteresis();
    json += "}]";
    server.send(200, "application/json", json);
}

void setup(void)
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");
  // pinMode(relay1,OUTPUT);
  // pinMode(relay2,OUTPUT);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/handleSettings", handleSettings);
  server.on("/toggleRelay1", [&]() {relayController(relay1);});
  server.on("/toggleRelay2", [&]() {relayController(relay2);});
  server.on("/st1", [&]() {relayStatus(relay1);});
  server.on("/st2", [&]() {relayStatus(relay2);});
  server.on("/readTemp", [&]() {sensorRead(SENSORS::TEMP);});
  server.on("/readHum", [&]() {sensorRead(SENSORS::HUM);});
  server.on("/readUptime", uptime);
  server.on("/data", HTTP_GET, jsonProcessor);

  httpUpdater.setup(&server, "/firmware");


  server.begin();
}

void loop(void)
{
  server.handleClient();
}
