#include "main.h"

void handleOn() {
  digitalWrite(12, HIGH);
  httpServer.send(302, "text/plain", "On");
}

void handleOff() {
  digitalWrite(12, LOW);
  httpServer.send(302, "text/plain", "Off");
}

void relayController()
{
  byte state = digitalRead(12);
  digitalWrite(12, !state);

  httpServer.send(200, "text/plane", String(!state));
}

void handleRoot() {
  String s = webpage;
  httpServer.send(200, "text/html", s);
}

void handleSt() {
  httpServer.send(200, "text/plain", String(digitalRead(12)));
}

void handleDev() {
  
  String ssid = WiFi.SSID();
  String macAddress = WiFi.macAddress();
  String ip = WiFi.localIP().toString();
  String uptime = uptime_formatter::getUptime();
  String state = String(digitalRead(12));

  String jsonString = "[";
  jsonString += "{";
  jsonString += "\"SSID\":\"" + ssid + "\",";
  jsonString += "\"MAC\":\"" + macAddress + "\",";
  jsonString += "\"IP\":\"" + ip + "\",";
  jsonString += "\"Uptime\":\"" + uptime + "\"";
  jsonString += "},";
  jsonString += "{";
  jsonString += "\"State\":\"" + state + "\"";
  jsonString += "}";
  jsonString += "]";

  httpServer.send(302, "text/plain", jsonString);
}

void uptime() {
  httpServer.send(200, "text/plane", uptime_formatter::getUptime());
}

void otaUpdater() {
  httpUpdater.setup(&httpServer, "/firmware");
  httpServer.on("/", handleRoot);
  httpServer.on("/dev", handleDev);
  httpServer.on("/st", handleSt);
  httpServer.on("/on", handleOn);
  httpServer.on("/off", handleOff);
  httpServer.on("/toggleRelay1", relayController);
  httpServer.on("/readUptime", uptime);
  httpServer.begin();
}

void buttonRelay() {
  if (digitalRead(12) == 0) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
}

void setup() {
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite (13, HIGH);
  // digitalWrite (12, HIGH);
  delay(100);
  wifiManager.autoConnect("Sonoff Connect");
  otaUpdater();
  digitalWrite (13, LOW);
}

void loop() {
  httpServer.handleClient();
  if (btn1.click())
    buttonRelay();
}
