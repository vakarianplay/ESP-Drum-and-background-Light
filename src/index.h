#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Streaming.h>
#include <uptime_formatter.h>


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

      <a href="/handleDrum"><button style="background:@@color_drum@@;" type="submit" name="state">УДРК</button></a>
      <br>

      <a href="/handleLed"><button style="background:@@color_led@@;" type="submit" name="state">СВЕТ</button></a>
      <br>
      <br><br><br>
      <form method="post" action="/form" name="pick">

        <input style="background:@@color@@;" type="color" name="color" value="@@color@@" onchange="document.forms['pick'].submit();">
        <br>
        <span onclick="document.forms['pick'].submit();"></span>
      </form>

  <br><br><br>

    <h3>@@uptime@@</h3>
    <br>

  </body>
  </html>


)=====";
