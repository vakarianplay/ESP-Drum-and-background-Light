#include "main.h"

void handleRoot() {
  String streamingUrl = preferences.getString("streamingUrl", "");
  int scrollingSpeed = preferences.getInt("scrollingSpeed", 0);

  String s = webpage;
  s.replace("{stream}", streamingUrl);
  s.replace("{speed}", String(scrollingSpeed));
  server.send(200, "text/html", s);
}

void handleSave() {
  String streamingUrl = server.arg("streamingUrl");
  int scrollingSpeed = server.arg("scrollingSpeed").toInt();

  Serial.print("Received Streaming Url: ");
  Serial.println(streamingUrl);
  Serial.print("Received Scrolling Speed: ");
  Serial.println(scrollingSpeed);
  server.send(200, "text/plain", "Parametrs save. Device rebooting...");

  preferences.putString("streamingUrl", streamingUrl);
  preferences.putInt("scrollingSpeed", scrollingSpeed);
  preferences.end();

  delay(1000);

  ESP.restart();
}

String httpData() {
  String dataget = dataGrabber.getData();
  return dataget;
}

void setup() {
  Serial.begin(9600);
  preferences.begin("my-app", false);
  dataGrabber.setupUrl(preferences.getString("streamingUrl", ""));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  httpUpdater.setup(&server, "/firmware");
  server.begin();
}

void loop() {
  server.handleClient();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    String data = httpData();
    Serial.println(data);
  }
}

