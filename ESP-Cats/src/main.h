#include <ESP8266WiFi.h>
#include <FastBot.h>
#include <Streaming.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#define WIFI_SSID "NullTempNet"
#define WIFI_PASS "12345678"
#define BOT_TOKEN "API"
#define CHAT_ID "1401259988"

FastBot bot(BOT_TOKEN);
WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \n Датчик движения \n Обновление прошивки \t Состояние сети");
String verBuild = "Версия прошивки: 0.04 test";
bool movingFlag = 1;
const int sensorPin = 15;
int curMode;
unsigned long lastTime;
