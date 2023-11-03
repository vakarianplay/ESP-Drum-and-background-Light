
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "index.h"

const byte relay1 = 15;
const byte relay2 = 13;
const char* ssid = "ASS WE CAN";
const char* password = "13371488";

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80);


void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void sensorReadTemp() 
{
 String sensor_value = String(analogRead(A0));
 server.send(200, "text/plane", sensor_value);
}

void relayController(byte relayNum) 
{
  byte state = digitalRead(relayNum);
  digitalWrite(relayNum, !state);
 
  server.send(200, "text/plane", String(!state));
}

void relayStatus(byte relayNum) {
    server.send(200, "text/plane", String(digitalRead(relayNum)));
}

void jsonProcessor() {
  String json = "{";
    json += "\"Relay_1\": " + String(digitalRead(relay1)) + ",";
    json += "\"Relay_2\": " + String(digitalRead(relay2)) + ",";
    json += "\"Sensor\": " + String(analogRead(A0));
    json += "}";
    server.send(200, "application/json", json);
}

void setup(void)
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(relay1,OUTPUT); 
  pinMode(relay2,OUTPUT); 
  
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
  server.on("/toggleRelay1", [&]() {relayController(relay1);});
  server.on("/toggleRelay2", [&]() {relayController(relay2);});
  server.on("/st1", [&]() {relayStatus(relay1);});
  server.on("/st2", [&]() {relayStatus(relay2);});
  server.on("/readTemp", sensorReadTemp);
  server.on("/data", HTTP_GET, jsonProcessor);

  httpUpdater.setup(&server, "/firmware");


  server.begin();
}

void loop(void)
{
  server.handleClient();
}