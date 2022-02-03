// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
//
// /* Установить свой SSID и пароль */
// const char* ssid = "WeMOS";
// const char* password = "12345678";
//
// /* Настройка IP-адрес */
// IPAddress local_ip(192,168,4,1);
// IPAddress gateway(192,168,4,1);
// IPAddress subnet(255,255,255,0);
//
// ESP8266WebServer server(80);
//
// uint8_t LED1pin = D4;
// bool LED1status = LOW;
//
// uint8_t LED2pin = D5;
// bool LED2status = LOW;
//
//
// void loop() {
//   server.handleClient();
//   if(LED1status)
//   {digitalWrite(LED1pin, HIGH);}
//   else
//   {digitalWrite(LED1pin, LOW);}
//
//   if(LED2status)
//   {digitalWrite(LED2pin, HIGH);}
//   else
//   {digitalWrite(LED2pin, LOW);}
// }
//
//
// String SendHTML(uint8_t led1stat,uint8_t led2stat){
//   String ptr = "<!DOCTYPE html> <html>\n";
//   ptr +="<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
//   ptr +="<title>Управление светодиодом</title>\n";
//   ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
//   ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
//   ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
//   ptr +=".button-on {background-color: #3498db;}\n";
//   ptr +=".button-on:active {background-color: #2980b9;}\n";
//   ptr +=".button-off {background-color: #34495e;}\n";
//   ptr +=".button-off:active {background-color: #2c3e50;}\n";
//   ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
//   ptr +="</style>\n";
//   ptr +="</head>\n";
//   ptr +="<body>\n";
//   ptr +="<h1>ESP8266 Веб сервер</h1>\n";
//     ptr +="<h3>Режим точка доступа WiFi (AP)</h3>\n";
//
//    if(led1stat)
//   {ptr +="<p>Состояние LED1: ВКЛ.</p><a class=\"button button-off\" href=\"/led1off\">ВЫКЛ.</a>\n";}
//   else
//   {ptr +="<p>Состояние LED1: ВЫКЛ.</p><a class=\"button button-on\" href=\"/led1on\">ВКЛ.</a>\n";}
//
//   if(led2stat)
//   {ptr +="<p>Состояние LED2: ВКЛ.</p><a class=\"button button-off\" href=\"/led2off\">ВЫКЛ.</a>\n";}
//   else
//   {ptr +="<p>Состояние LED2: ВЫКЛ.</p><a class=\"button button-on\" href=\"/led2on\">ВКЛ.</a>\n";}
//
//   ptr +="</body>\n";
//   ptr +="</html>\n";
//   return ptr;
// }
//
// void handle_OnConnect() {
//   LED1status = LOW;
//   LED2status = LOW;
//   Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
//   server.send(200, "text/html", SendHTML(LED1status,LED2status));
// }
//
// void handle_led1on() {
//   LED1status = HIGH;
//   Serial.println("GPIO7 Status: ON");
//   server.send(200, "text/html", SendHTML(true,LED2status));
// }
//
// void handle_led1off() {
//   LED1status = LOW;
//   Serial.println("GPIO7 Status: OFF");
//   server.send(200, "text/html", SendHTML(false,LED2status));
// }
//
// void handle_led2on() {
//   LED2status = HIGH;
//   Serial.println("GPIO6 Status: ON");
//   server.send(200, "text/html", SendHTML(LED1status,true));
// }
//
// void handle_led2off() {
//   LED2status = LOW;
//   Serial.println("GPIO6 Status: OFF");
//   server.send(200, "text/html", SendHTML(LED1status,false));
// }
//
// void handle_NotFound(){
//   server.send(404, "text/plain", "Not found");
// }
//
//
//
// void setup() {
//   Serial.begin(9600);
//   pinMode(LED1pin, OUTPUT);
//   pinMode(LED2pin, OUTPUT);
//
//  WiFi.softAPConfig(local_ip, gateway, subnet);
//  WiFi.mode(WIFI_AP);
//  WiFi.softAP(ssid, password);
//
//   server.on("/", handle_OnConnect);
//   server.on("/led1on", handle_led1on);
//   server.on("/led1off", handle_led1off);
//   server.on("/led2on", handle_led2on);
//   server.on("/led2off", handle_led2off);
//   server.onNotFound(handle_NotFound);
//
//   server.begin();
//   Serial.println("HTTP server started");
// }

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//SSID and Password of your WiFi router
const char* ssid = "WeMOS";
const char* password = "12345678";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//LED Connections
const int RedLED=15;     //D8  GPIO15
const int GreenLED=12;  //D6  GPIO12
const int BlueLED=13;    //D7  GPIO13

String setcolor="#0284e0";
String setcolor_off="#34495e"; //Set color for HTML

const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="utf-8" name="viewport" content="width=device-width initial-scale=1">

  <title>TEST</title>
  <style media="screen">
    html
    { font-family: Helvetica;
      display: inline-block;
      margin: 0px auto;
      text-align: center;}
      body{margin-top: 50px;}
      h1 {color: #444444;margin: 50px auto 30px;}
      h3 {color: #444444;margin-bottom: 10px;}
      button {
        width: 150px;
		height: 65px;
        border: none;
        color: white;
        padding: 13px 30px;
        text-decoration: none;
        font-size: 21px;
        margin: 1px auto 35px;
        cursor: pointer;
        border-radius: 4px;
        box-shadow: 0 0 10px rgba(0,0,0,0.5); /* Параметры тени */
        padding: 10px;
      }
        input {
          width: 80px;
		  height: 65px;
          box-shadow: 0 0 10px rgba(0,0,0,0.5); /* Параметры тени */
          padding: 10px;
          border: none;
          color: white;
          padding: 13px 30px;
          text-decoration: none;
          margin: 0px auto 35px;
          cursor: pointer;
          border-radius: 4px;}
        .set {
          background-color: #3498db;
          color: white;
        }


  </style>
  </head>
  <body>


      <h1>Контроллер тест</h1>
      <br><br>

      <button style="background:@@color_drum@@;" type="submit" name="state" value="@@mode1@@">УДРК</button>
      <br>

      <button style="background:@@color_led@@;" type="submit" name="state" value="@@mode1@@">СВЕТ</button>
      <br>
      <br><br><br>
    <form method="post" action="/form">

        <input style="background:@@color@@;" type="color" name="color" value="@@color@@">
		<br>
        <button class="set" type="submit" name="state" value="stop">УСТ</button>
    </form>
  <br><br><br>

  </body>
  </html>

)=====";

//=======================================================================
//                    handles main page
//=======================================================================
void handleRoot() {
  String p = MAIN_page;
  p.replace("@@color@@",setcolor);
  p.replace("@@color_drum@@",setcolor_off);
  p.replace("@@color_led@@",setcolor_off);    //Set page background color and selected color
  server.send(200, "text/html", p);
}

//=======================================================================
//                    Handle Set Color
//=======================================================================
void handleForm() {
  String color = server.arg("color");
  //form?color=%23ff0000
  setcolor = color; //Store actual color set for updating in HTML
  Serial.println(color);

  //See what we have recived
  //We get #RRGGBB in hex string

  // Get rid of '#' and convert it to integer, Long as we have three 8-bit i.e. 24-bit values
  long number = (int) strtol( &color[1], NULL, 16);

  //Split them up into r, g, b values
  long r = number >> 16;
  long g = (number >> 8) & 0xFF;
  long b = number & 0xFF;

  //PWM Correction
  r = r * 4;
  g = g * 4;
  b = b * 4;
//for ULN2003 or Common Cathode RGB LED not needed
/*
  r = 1024 - r;
  g = 1024 - g;
  b = 1024 - b;
*/
  //ESP supports analogWrite All IOs are PWM
  analogWrite(RedLED,r);
  analogWrite(GreenLED,g);
  analogWrite(BlueLED,b);

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");

  delay(500);
}
//=======================================================================
//                    SETUP
//=======================================================================
void setup(){
  Serial.begin(9600);   //Start serial connection

  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(BlueLED,OUTPUT);

   WiFi.softAPConfig(local_ip, gateway, subnet);
   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password);

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);  //Associate handler function to path
  server.on("/form",handleForm);

  server.begin();                           //Start server
  Serial.println("HTTP server started");
}
//=======================================================================
//                    LOOP
//=======================================================================
void loop(){
  server.handleClient();
}
