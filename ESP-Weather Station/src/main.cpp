#include "main.h"

void otaUpdater() {
  httpUpdater.setup(&httpServer, "/firmware");
  httpServer.begin();
}

String getIp() {
  String ip = WiFi.localIP().toString();
  int index = ip.lastIndexOf('.');
  int length = ip.length();
  String cutIP = ip.substring(index -1, length);
  return cutIP;
}

void drawProgress(OLEDDisplay *display, int percentage, String label) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(2, 28, 124, 10, percentage);
  display->display();
}

void wttrSplit(String wttrGet) {
  StaticJsonDocument<2000> jsonBuffer;
  DeserializationError error = deserializeJson(jsonBuffer, wttrGet);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    delay(5000);
    return;
  }
  String weather = jsonBuffer["temp"];
  wttrVar.wttrinWeather = weather;
  String cap = jsonBuffer["caption"];
  wttrVar.wttrinCaption = cap;
  String hum = jsonBuffer["humidity"];
  wttrVar.wttrinHumidity = hum;
  String press = jsonBuffer["pressure"];
  wttrVar.wttrinPressure = press;
  String wind = jsonBuffer["wind"];
  wttrVar.wttrinWind = wind;
}

void wttrGet() {
  String wttrGet;
  HTTPClient http;
    http.begin("https://wttr.in/Electrostal?format={%22temp%22:%22%t%20(%f)%22,%20%22caption%22:%22%C%22,%22humidity%22:%22%h%22,%20%22pressure%22:%22%P%22,%20%22wind%22:%22%w%22}");
    int httpCode = http.GET();
    if (httpCode > 0) {
      wttrGet = http.getString();
      wttrSplit(wttrGet);
    }
    http.end();
}

void dhtGet() {
  String wttrGet;
  HTTPClient http;
    http.begin("http://192.168.1.253/temp");
    int httpCode = http.GET();
    if (httpCode > 0) {
      dhtVar.dhtTemp = http.getString();
    }
    http.end();
    http.begin("http://192.168.1.253/hum");
    httpCode = http.GET();
    if (httpCode > 0) {
      dhtVar.dhtHum = http.getString();
    }
    http.end();
}

void narodJsonGet() {

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.println("GET /api/sensorsOnDevice?id=7689&uuid={place_your_uid}&api_key={narodmon_API_key}&lang=en HTTP/1.1");
  client.println("Host: narodmon.ru");
  client.println("Connection: close");
  client.println();

  delay(1000);
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    narodLine = client.readStringUntil('\r');
  }
  Serial.print(narodLine);
  Serial.println();
  Serial.println("closing connection");
}

void narodData() {
  narodJsonGet();
  StaticJsonDocument<2000> jsonBuffer;
  DeserializationError error = deserializeJson(jsonBuffer, narodLine);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    delay(5000);
    return;
  }
  else {
    Serial.println("There are no errors");

  }

  float value = jsonBuffer["sensors"][0]["value"];
  Serial.print(value);
  narodRadValue = String(value);

  float value = jsonBuffer["sensors"][1]["value"];
  Serial.print(value);
  narodValue = String(value);
}

void updateData(OLEDDisplay *display) {
  drawProgress(display, 10, "Updating time...");
  delay(300);

  drawProgress(display, 30, "Updating NarodMon");
  narodData();

  drawProgress(display, 50, "Updating WttrIn");
  wttrGet();

  drawProgress(display, 80, "Updating DHT");
  dhtGet();

  lastUpdate = ntp.timeString();
  readyForWeatherUpdate = false;
  drawProgress(display, 100, "Done...");
  delay(1000);
}

void drawDateTime(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  String date = ntp.dateString();
  int textWidth = display->getStringWidth(date);
  display->drawString(64 + x, 5 + y, date);
  display->setFont(ArialMT_Plain_24);
  String time = ntp.timeString();
  textWidth = display->getStringWidth(time);
  display->drawString(64 + x, 15 + y, time);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void drawNarodMon(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(Roboto_12);
  display->drawString(64 + x, 0 + y, "NarodMon");
  display->setFont(ArialMT_Plain_24);
  display->drawString(64 + x, 14 + y, narodValue + "°C");
}

void drawNarodMonRad(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(Roboto_12);
  display->drawString(64 + x, 0 + y, "Radiation");
  display->setFont(ArialMT_Plain_24);
  display->drawString(64 + x, 14 + y, narodRadValue + "μR/H");
}

void drawCurrentWeather(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setFont(Roboto_12);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(60 + x, 5 + y, wttrVar.wttrinCaption);

  display->setFont(ArialMT_Plain_16);
  display->drawString(60 + x, 20 + y, wttrVar.wttrinWeather);
  int tempWidth = display->getStringWidth(wttrVar.wttrinWeather);
}

void drawDht(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  String displayDht = dhtVar.dhtTemp + "°C " + dhtVar.dhtHum + "%";

  display->setFont(Roboto_12);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(60 + x, 5 + y, "DHT11");

  display->setFont(ArialMT_Plain_16);
  display->drawString(65 + x, 22 + y, displayDht);
  int tempWidth = display->getStringWidth(displayDht);
}

void drawDetailsWeather(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setFont(Roboto_12);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(60 + x, 5 + y, "Humidity: " + wttrVar.wttrinHumidity);

  display->setFont(Roboto_12);
  display->drawString(60 + x, 20 + y, "Press: " + wttrVar.wttrinPressure);

  display->setFont(Roboto_12);
  display->drawString(60 + x, 36 + y, "Wind: " + wttrVar.wttrinWind);

}
//
//
// void drawForecast(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
//   drawForecastDetails(display, x, y, 0);
//   drawForecastDetails(display, x + 44, y, 2);
//   drawForecastDetails(display, x + 88, y, 4);
// }



// void drawForecastDetails(OLEDDisplay *display, int x, int y, int dayIndex) {
//   display->setTextAlignment(TEXT_ALIGN_CENTER);
//   display->setFont(ArialMT_Plain_10);
//   String day = wunderground.getForecastTitle(dayIndex).substring(0, 3);
//   day.toUpperCase();
//   display->drawString(x + 20, y, day);
//
//   display->setFont(Meteocons_Plain_21);
//   display->drawString(x + 20, y + 12, wunderground.getForecastIcon(dayIndex));
//
//   display->setFont(ArialMT_Plain_10);
//   display->drawString(x + 20, y + 34, wunderground.getForecastLowTemp(dayIndex) + "|" + wunderground.getForecastHighTemp(dayIndex));
//   display->setTextAlignment(TEXT_ALIGN_LEFT);
// }

void drawHeaderOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setColor(WHITE);
  display->setFont(Roboto_8);
  String time = ntp.timeString();
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 54, time);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  // String ip = WiFi.localIP().toString();
  display->drawString(128, 54, getIp());
  display->drawHorizontalLine(0, 52, 128);
}

void setReadyForWeatherUpdate() {
  readyForWeatherUpdate = true;
}


void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();


  // initialize dispaly
  display.init();
  display.clear();
  display.display();

  //display.flipScreenVertically();
  // display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setContrast(255);

  display.setFont(Roboto_12);
  display.drawString(60, 12, "Config WiFi:");
  display.drawString(60, 26, "EspWeatherAP");
  display.display();
  wifiManager.autoConnect("EspWeatherAP");
  // WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.clear();
    display.drawString(64, 10, "Connecting to WiFi");
    display.drawXbm(46, 30, 8, 8, counter % 3 == 0 ? activeSymbole : inactiveSymbole);
    display.drawXbm(60, 30, 8, 8, counter % 3 == 1 ? activeSymbole : inactiveSymbole);
    display.drawXbm(74, 30, 8, 8, counter % 3 == 2 ? activeSymbole : inactiveSymbole);
    display.display();

    counter++;
  }

  ntp.begin();
  otaUpdater();

  ui.setTargetFPS(30);
  ui.setActiveSymbol(activeSymbole);
  ui.setInactiveSymbol(inactiveSymbole);
  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);
  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);
  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_TOP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, numberOfFrames);
  ui.setOverlays(overlays, numberOfOverlays);
  ui.setTimePerFrame(8000);
  // Inital UI takes care of initalising the display too.
  ui.init();

  updateData(&display);
}

void loop() {
  ntp.tick();
  httpServer.handleClient();



  if (millis() - timeSinceLastWUpdate > (1000L*UPDATE_INTERVAL_SECS)) {
    setReadyForWeatherUpdate();
    timeSinceLastWUpdate = millis();
  }

  if (readyForWeatherUpdate && ui.getUiState()->frameState == FIXED) {
    updateData(&display);
  }

  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }


}
