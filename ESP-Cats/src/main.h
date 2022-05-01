#include <ESP8266WiFi.h>
#include <Servo.h>
#include <FastBot.h>
#include <Streaming.h>
#define WIFI_SSID "SSID HERE"
#define WIFI_PASS "WIFI PASS HERE"
#define BOT_TOKEN "API KEY"
#define CHAT_ID "CHAT ID" //optional

FastBot bot(BOT_TOKEN);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \n Датчик движения \n Обновление прошивки");
String verBuild = "Версия прошивки: 0.03 night";
bool movingFlag = 1;
const int sensorPin = 15;
int curMode;
unsigned long lastTime;
