#include "main.h"

void handleOn() {
  digitalWrite(12, HIGH);
  httpServer.send(302, "text/plain", "On");
}

void handleOff() {
  digitalWrite(12, LOW);
  httpServer.send(302, "text/plain", "Off");
}

void handleRoot() {
  // String root = "Имя сети: " + WiFi.SSID() + " | MAC: " + WiFi.macAddress() + " | IP: " + WiFi.localIP().toString();
  httpServer.send(302, "text/plain", String(digitalRead(12)));
}

void otaUpdater() {
  httpUpdater.setup(&httpServer, "/firmware");
  httpServer.on("/", handleRoot);
  httpServer.on("/on", handleOn);
  httpServer.on("/off", handleOff);
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
  delay(100);
  wifiManager.autoConnect("WeMos Connect");
  otaUpdater();
  digitalWrite (13, LOW);
}



void loop() {
  httpServer.handleClient();
  if (btn1.click())
    buttonRelay();
}
