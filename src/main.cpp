#include "index.h"
//SSID and Password
const char* ssid = "MetalLight";
const char* password = "12345678";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//LED pins
const int RedLED=15;     //D8  GPIO15
const int GreenLED=12;  //D6  GPIO12
const int BlueLED=13;    //D7  GPIO13
const int sensorRed=14;    //D5 GPIO14
const int sensorBlue=16; //D0 GPIO16

// const int ledboard=2;

int init_c=0;

// colors for buttons
struct server_var {
  String setcolor;
  String mode_drum;
  String mode_led;
};
server_var colors = {"#e0e0e0" , "#808080", "#808080"};

//states of modes
struct states {
  bool drum_state;
  bool led_state;
};
states mode = {false, false};


//=======================================================================
//                    handles main page
//=======================================================================
void handleRoot() {
  String p = MAIN_page;
  p.replace("@@color@@",colors.setcolor); //Set button colors
  p.replace("@@color_drum@@",colors.mode_drum);
  p.replace("@@color_led@@",colors.mode_led);
  p.replace("@@uptime@@", uptime_formatter::getUptime()); //Set uptime data
  Serial << uptime_formatter::getUptime() << endl;

  server.send(200, "text/html", p);
}

//active button drum
void btn_drum(){
  colors.mode_led = "#808080";
  colors.mode_drum ="#e0e0e0";
}

//active button led
void btn_led(){
  colors.mode_led = "#e0e0e0";
  colors.mode_drum ="#808080";
}

//inactive buttons
void btn_off(){
  colors.mode_led = "#808080";
  colors.mode_drum ="#808080";
  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);
  digitalWrite(BlueLED, LOW);
}

// setup color
void handleForm() {

  String getcolor = server.arg("color"); //form?color=%23ff0000

  //check correct data
  if (getcolor.length() == 7) {
   colors.setcolor = getcolor;
  }

  String color = colors.setcolor;   //#RRGGBB hex string

  mode.led_state = true;
  mode.drum_state = false; //update button
  btn_led();
  Serial << color << "_" << getcolor.length() << endl;

  // Get rid of '#' and convert it to dec numbers
  long number = (int) strtol( &color[1], NULL, 16);

  //Split them up into r, g, b values
  long r = number >> 16;
  long g = (number >> 8) & 0xFF;
  long b = number & 0xFF;

  Serial <<"\n" << "R: " << r << " G: " << g << " B:" << b << "\n" <<endl;

  // set PWM value to pins
  analogWrite(RedLED,r);
  analogWrite(GreenLED,g);
  analogWrite(BlueLED,b);

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated");

  delay(500);
}

void handleDrum()
{ //check active mode and set actual status
  if ((mode.drum_state == false && mode.led_state == false) || (mode.drum_state == false && mode.led_state == true) ) {
    mode.drum_state = true;
    mode.led_state = false;
    digitalWrite(RedLED, LOW);
    digitalWrite(GreenLED, LOW);
    digitalWrite(BlueLED, LOW);
    btn_drum();
    Serial << "drum on" << endl;
  } else {
    mode.drum_state = false;
    btn_off();
    Serial << "drum off" << endl;
  }

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated drum state");

  delay(500);
// return 1;
}

void handleLed(){
  if ((mode.drum_state == false && mode.led_state == false) || (mode.drum_state == true && mode.led_state == false) ) {
    mode.drum_state = false;
    mode.led_state = true;
    btn_led();
    Serial << "led on" << endl;
    handleForm();
  } else {
    mode.led_state = false;
    btn_off();
    Serial.print("led off");
    Serial << "led off" << endl;  }

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated light state");

  delay(500);
// return 1;
}

void start_init()
{
  while (init_c < 1)
  {
    digitalWrite(RedLED, HIGH);
    Serial << "RED INIT ";
    delay(50);
    digitalWrite(GreenLED, HIGH);
    Serial << "GREEN INIT ";
    delay(50);
    digitalWrite(BlueLED, HIGH);
    Serial << "BLUE INIT ";
    delay(100);
    digitalWrite(RedLED, LOW);
    digitalWrite(GreenLED, LOW);
    digitalWrite(BlueLED, LOW);
    Serial << "off and ready" << endl;
    init_c +=1;
  }
}

void sensors ()
{
  if (mode.drum_state == true) {
    if (digitalRead(sensorRed) == 1) {
      Serial << "SENSOR RED" << endl;
      digitalWrite(RedLED, HIGH);
      delay (50);
      digitalWrite(RedLED, LOW);
    }
    if (digitalRead(sensorBlue) == 1) {
      Serial << "SENSOR BLUE" << endl;
      digitalWrite(BlueLED, HIGH);
      delay (50);
      digitalWrite(BlueLED, LOW);
    }
    if (digitalRead(sensorBlue) == 1 && digitalRead(sensorRed) == 1) {
      Serial << "SENSOR BLUE AND RED" << endl;
      digitalWrite(BlueLED, HIGH);
      digitalWrite(RedLED, HIGH);
      delay (50);
      digitalWrite(BlueLED, LOW);
      digitalWrite(RedLED, LOW);
    }
  }
}

//SETUP
void setup(){
  Serial.begin(9600);   //Start serial

  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(BlueLED,OUTPUT);
  pinMode(sensorRed,INPUT_PULLUP);
  pinMode(sensorBlue,INPUT_PULLUP);

   WiFi.softAPConfig(local_ip, gateway, subnet); //Create AP mode
   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password);

  Serial << "AP Mode: " << ssid << " " << password << "\n" << endl;  //Debug for AP info

  server.on("/", handleRoot);  //Associate handler function to path
  server.on("/form",handleForm);
  server.on("/handleDrum", handleDrum);
  server.on("/handleLed", handleLed);

  server.begin();   //Start server
  Serial << "HTTP server started" << "\n" << endl;

  start_init();
}

// LOOP
void loop(){
  server.handleClient();
  sensors();
}
