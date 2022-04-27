#include <ESP8266WiFi.h>
#include <Servo.h>
#include <FastBot.h>
#include <Streaming.h>
#define WIFI_SSID "ASS WE CAN"
#define WIFI_PASS "13371488"
#define BOT_TOKEN "1933129297:AAFtgv9LaOgDbT6fUKnIbd1rBsVCrIA_k2o"
#define CHAT_ID "1401259988"

FastBot bot(BOT_TOKEN);
String menu1 = ("РЕЖИМ 1 \t РЕЖИМ 2 \t РЕЖИМ 3 \n Датчик движения");
bool movingFlag = 1;
