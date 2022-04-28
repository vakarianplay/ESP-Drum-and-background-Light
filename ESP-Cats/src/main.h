#include <ESP8266WiFi.h>
#include <Servo.h>
#include <FastBot.h>
#include <Streaming.h>
#define WIFI_SSID "SSID HERE"
#define WIFI_PASS "WIFI PASS HERE"
#define BOT_TOKEN "API KEY"
#define CHAT_ID "CHAT ID"

FastBot bot(BOT_TOKEN);
String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \n Датчик движения");
bool movingFlag = 1;
