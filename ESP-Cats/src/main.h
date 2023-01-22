#include <ESP8266WiFi.h>
#include <FastBot.h>
#include <Streaming.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "motordriver.h"

#define BOT_TOKEN "1933129297:AAFtgv9LaOgDbT6fUKnIbd1rBsVCrIA_k2o"
#define CHAT_ID "1401259988"

FastBot bot(BOT_TOKEN);
WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \t РЕЖИМ 4 \n Датчик движения \n Обновление прошивки \t Состояние сети");
String verBuild = "Версия прошивки: 0.051 moving test";
bool movingFlag = 1;
// const int sensorPin = 15;
const uint8_t indicatorRed = 5; //D1
const uint8_t indicatorGreen = 4; //D2
uint8_t curMode;
unsigned long lastTime;

MotorDriver motor(15, 13);
