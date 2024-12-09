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
  Value: <input type="text" name="value" id="value" value="%s"><br>
  <input type="submit" value="Save">
</form>
</body>
</html>
)rawliteral";

void handleRoot() {
  String value = preferences.getString("value", "");
  Serial.println(value);
  char html[512];
  sprintf(html, indexHTML, value.c_str());
  server.send(200, "text/html", html);
}

void handleSave() {
  String value = server.arg("value");
  Serial.print("Received value: ");
  Serial.println(value);

  preferences.putString("value", value);
  preferences.end();
  server.send(200, "text/plain", "Value saved");
  ESP.restart();
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