#include <Arduino.h>
#include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Streaming.h>
#include <AsyncElegantOTA.h>


// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASS";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

//LED pins
const int RedLED=15;     //D8  GPIO15
const int GreenLED=12;  //D6  GPIO12
const int BlueLED=13;    //D7  GPIO13

float smoothness_pts = 500;
float g = 0.14;
float b = 0.5;
int triangleFlag = 0;
int circleFlag = 0;
int gaussianFlag = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
