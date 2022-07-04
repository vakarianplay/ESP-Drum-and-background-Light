#include "main.h"

void handleOn() {
  digitalWrite(relayPin, HIGH);
  httpServer.send(302, "text/plain", "On");
}

void handleOff() {
  digitalWrite(relayPin, LOW);
  httpServer.send(302, "text/plain", "Off");
}

void handleRoot() {
  String root = "SSID: " + WiFi.SSID() + " | MAC: " + WiFi.macAddress() + " | IP: " + WiFi.localIP().toString();
  httpServer.send(302, "text/plain", root);
}

void otaUpdater() {
  httpUpdater.setup(&httpServer, "/firmware");
  httpServer.on("/", handleRoot);
  httpServer.on("/on", handleOn);
  httpServer.on("/off", handleOff);
  httpServer.begin();
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite (ledPin, HIGH);
  delay(100);
  wifiManager.autoConnect("Sonoff Connect");
  otaUpdater();
  digitalWrite (ledPin, LOW);
}

void loop() {
  httpServer.handleClient();
}
