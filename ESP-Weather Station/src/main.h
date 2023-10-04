#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPUpdateServer.h>
#include <WebServer.h>
#include <SSD1306Wire.h>
#include <GyverNTP.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
#include "OLEDDisplayUi.h"
// #include "WeatherStationFonts.h"
#include "WeatherStationImages.h"
#include "robotofont.h"

const int UPDATE_INTERVAL_SECS = 30 * 60;


SSD1306Wire display(0x3c, 5, 4);
OLEDDisplayUi   ui( &display );
WiFiManager wifiManager;
GyverNTP ntp(3);
HTTPUpdateServer httpUpdater;
WebServer httpServer(80);

const char* host = "narodmon.ru";
String narodLine;
String narodValue;

struct wttrStruct{
  String wttrinWeather;
  String wttrinCaption;
  String wttrinHumidity;
  String wttrinPressure;
  String wttrinWind;
};

struct dhtStruct{
  String dhtTemp;
  String dhtHum;
};

wttrStruct wttrVar;
dhtStruct dhtVar;

bool readyForWeatherUpdate = false;
String lastUpdate = "--";
long timeSinceLastWUpdate = 0;

void drawProgress(OLEDDisplay *display, int percentage, String label);
void updateData(OLEDDisplay *display);
void drawDateTime(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawCurrentWeather(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawDetailsWeather(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
// void drawForecast(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawNarodMon(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawNarodMonRad(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawDht(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
// void drawForecastDetails(OLEDDisplay *display, int x, int y, int dayIndex);
void drawHeaderOverlay(OLEDDisplay *display, OLEDDisplayUiState* state);
void setReadyForWeatherUpdate();

FrameCallback frames[] = { drawDateTime, drawCurrentWeather, drawDetailsWeather, drawNarodMon, drawNarodMonRad drawDht };
int numberOfFrames = 6;


OverlayCallback overlays[] = { drawHeaderOverlay };
int numberOfOverlays = 1;
