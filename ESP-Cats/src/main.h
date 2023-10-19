#include <ESP8266WiFi.h>
#include <FastBot.h>
#include <Streaming.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "motordriver.h"

#define BOT_TOKEN "place_bot_token_here"
#define CHAT_ID "place_chat_id_here"

FastBot bot(BOT_TOKEN);
WiFiManager wifiManager;
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \t РЕЖИМ 4 \n Датчик движения \n Обновление прошивки \t Состояние сети");
String verBuild = "Версия прошивки: 0.052 moving test";
bool movingFlag = false;
const uint8_t sensorPin = 12;
const uint8_t indicatorRed = 5; //D1
const uint8_t indicatorGreen = 4; //D2
uint8_t curMode = 0;
unsigned long lastTime;
unsigned long lastIndication;
unsigned long lastIndicationMov;

MotorDriver motor(15, 13);
