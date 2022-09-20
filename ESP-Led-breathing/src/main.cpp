#include "main.h"
#include "index.h"

void triangleBreath ()
{
  if (triangleFlag == 1) {
    for (int i=0; i < smoothness_pts; i++){
    float pwm_val = 255.0*(1.0 -  abs((2.0*(i/smoothness_pts))-1.0));
    analogWrite(RedLED ,int(pwm_val));
    delay(5);
    }
  } else {
    digitalWrite(RedLED, LOW);
  }
}

void circleBreath ()
{
  if (circleFlag == 1) {
    for (int i=0; i <smoothness_pts; i++){
    float pwm_val = 255.0*sqrt(1.0 -  pow(abs((2.0*(i/smoothness_pts))-1.0),2.0));
    analogWrite(GreenLED, int(pwm_val));
    delay(5);
    }
  } else {
    digitalWrite(GreenLED, LOW);
  }
}

void gaussianBreath ()
{
  if (gaussianFlag == 1) {
    for (int i=0; i <smoothness_pts; i++){
    float pwm_val = 255.0*(exp(-(pow(((i/smoothness_pts) - b)/g,2.0))/2.0));
    analogWrite(BlueLED, int(pwm_val));
    delay(5);
    }
  } else {
    digitalWrite(BlueLED, LOW);
  }
}

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Triangle</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"1\" " + outputState(15) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Circle</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(12) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Gaussian</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"3\" " + outputState(13) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

void turnMode(int inputMessage1, int inputMessage2){
  if (inputMessage1 == 1) {
      triangleFlag = inputMessage2;
  }

  if (inputMessage1 == 2) {
      circleFlag = inputMessage2;
  }

  if (inputMessage1 == 3) {
      gaussianFlag = inputMessage2;
  }
}

void setup(){

  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/change", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      // digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
      turnMode(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    request->send(200, "text/plain", "OK");
  });


  // Start server
  AsyncElegantOTA.begin(&server);
  server.begin();
}

void loop() {
  triangleBreath();
  circleBreath();
  gaussianBreath();
}
