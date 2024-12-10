#include <ESP8266WebServer.h>
#include <Preferences.h>

const char* ssid = "roof";
const char* password = "12345618";

ESP8266WebServer server(80);
Preferences preferences;

const char indexHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<title>ESP32 Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
<h1>ESP32 Web Server</h1>
<form method="POST" action="/save">
  Streaming Url: <input type="text" name="streamingUrl" id="streamingUrl" value="%s"><br>
  Scrolling Speed: <input type="number" name="scrollingSpeed" id="scrollingSpeed" value="%d"><br>
  <input type="submit" value="Save">
</form>
</body>
</html>
)rawliteral";

void handleRoot() {
  String streamingUrl = preferences.getString("streamingUrl", "");
  int scrollingSpeed = preferences.getInt("scrollingSpeed", 0); // Default speed 0

  char html[512];
  sprintf(html, indexHTML, streamingUrl.c_str(), scrollingSpeed);
  server.send(200, "text/html", html);
}

void handleSave() {
  String streamingUrl = server.arg("streamingUrl");
  int scrollingSpeed = server.arg("scrollingSpeed").toInt(); // Convert string to integer

  Serial.print("Received Streaming Url: ");
  Serial.println(streamingUrl);
  Serial.print("Received Scrolling Speed: ");
  Serial.println(scrollingSpeed);

  preferences.putString("streamingUrl", streamingUrl);
  preferences.putInt("scrollingSpeed", scrollingSpeed);
  preferences.end();
  server.send(200, "text/plain", "Values saved");
}

void setup() {
  Serial.begin(9600);
  preferences.begin("my-app", false);

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
  server.begin();
}

void loop() {
  server.handleClient();
}

