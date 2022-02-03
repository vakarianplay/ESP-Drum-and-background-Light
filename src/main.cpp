#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"

//SSID and Password
const char* ssid = "WeMOS";
const char* password = "12345678";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//LED pins
const int RedLED=15;     //D8  GPIO15
const int GreenLED=12;  //D6  GPIO12
const int BlueLED=13;    //D7  GPIO13


struct server_var {
  String setcolor;
  String mode_drum;
  String mode_led;
};
server_var colors = {"#0284e0" , "#34495e", "#34495e"};

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
  p.replace("@@color@@",colors.setcolor);
  p.replace("@@color_drum@@",colors.mode_drum);
  p.replace("@@color_led@@",colors.mode_led);

     //Set page background color and selected color
  server.send(200, "text/html", p);
}

void btn_drum(){
  colors.mode_led = "#34495e";
  colors.mode_drum ="#1072cc";
}

void btn_led(){
  colors.mode_led = "#1072cc";
  colors.mode_drum ="#34495e";
}

void btn_off(){
  colors.mode_led = "#34495e";
  colors.mode_drum ="#34495e";
}

void drum_visual() {

if (mode.drum_state == true) {
  Serial.print("drum work");
  delay(300);
}
  }



// setup color
void handleForm() {

  String getcolor = server.arg("color"); //form?color=%23ff0000

  //check correct data
  if (getcolor.length() == 7) {
   colors.setcolor = getcolor;
  }

  String color = colors.setcolor;   //#RRGGBB hex string

  mode.led_state = true; //update button
  btn_led();
  Serial.println(color + "_" + getcolor.length());

  // Get rid of '#' and convert it to dec numbers
  long number = (int) strtol( &color[1], NULL, 16);

  //Split them up into r, g, b values
  long r = number >> 16;
  long g = (number >> 8) & 0xFF;
  long b = number & 0xFF;

  //PWM Correction
   // r = r * 4;
  Serial.println(r);
   // g = g * 4;
  Serial.println(g);
   // b = b * 4;
  Serial.println(b);

  // set PWM value to pins
  analogWrite(RedLED,r);
  analogWrite(GreenLED,g);
  analogWrite(BlueLED,b);

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated");

  delay(500);
}

void handleDrum(){
  if ((mode.drum_state == false && mode.led_state == false) || (mode.drum_state == false && mode.led_state == true) ) {
    mode.drum_state = true;
    mode.led_state = false;
    btn_drum();
    Serial.print("drum on");
    // drum_visual();
  } else {
    mode.drum_state = false;
    btn_off();
    Serial.print("drum off");
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
    Serial.print("led on");
    handleForm();
  } else {
    mode.led_state = false;
    btn_off();
    Serial.print("led off");
  }

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated light state");

  delay(500);
// return 1;
}

//SETUP
void setup(){
  Serial.begin(9600);   //Start serial

  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(BlueLED,OUTPUT);

   WiFi.softAPConfig(local_ip, gateway, subnet); //Create AP mode
   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password);

  Serial.print("AP Mode: "); //Debug info
  Serial.print(ssid);
  Serial.print(" ");
  Serial.print(password);
  Serial.print(" ");

  server.on("/", handleRoot);  //Associate handler function to path
  server.on("/form",handleForm);
  server.on("/handleDrum", handleDrum);
  server.on("/handleLed", handleLed);

  server.begin();                           //Start server
  Serial.println("HTTP server started");
}

// LOOP
void loop(){
  server.handleClient();

  if (mode.drum_state == true) {
    Serial.print("drum work");
    delay(300);
  }
}
