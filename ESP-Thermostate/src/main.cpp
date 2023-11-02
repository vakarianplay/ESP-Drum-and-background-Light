#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "index.h"

const char* ssid = "MUTINY";
const char* password = "816planet";
const int ledPin = 15;
bool isLedOn = false;

AsyncWebServer server(80);

void ledProcessor(AsyncWebServerRequest *request) {
  isLedOn = !isLedOn;
  String stateText = "";
  if (isLedOn) {
    digitalWrite(ledPin, HIGH);
    request->send(200, "text/plain", "Turn off");
  } else {
    digitalWrite(ledPin, LOW);
    request->send(200, "text/plain", "Turn on");
  }
}
void handleReadSensor(AsyncWebServerRequest *request) {
  int value = analogRead(A0);
  String response = String(value);
  request->send(200, "text/plain", response);
}

void jsonProcessor(AsyncWebServerRequest *request) {
  String json = "{";
    json += "\"Relay_1\": " + String(digitalRead(15)) + ",";
    json += "\"Sensor\": " + String(analogRead(A0));
    json += "}";
    request->send(200, "application/json", json);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  server.on("/toggleLed", HTTP_GET, ledProcessor);
  server.on("/readSensor", HTTP_GET, handleReadSensor);
  server.on("/data", HTTP_GET, jsonProcessor);

  // Настройка обработчика для главной страницы
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String buttonText = isLedOn ? "Turn off" : "Turn on";
    String webpage = html;
    webpage.replace("%btnTxt%", buttonText);

    request->send(200, "text/html", webpage);
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
}

void loop() {
  // Дополнительные задачи, если есть
}
