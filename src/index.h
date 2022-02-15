#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Streaming.h>
#include <uptime_formatter.h>


const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="utf-8" name="viewport" content="width=device-width initial-scale=1">

  <title>DRUM LIGHT</title>
  <style>
text {
   color: #ffffff;
  text-align: center;
  font-weight:bold;
}

footer {
   color: #878787;
  font-family: 'Courier New', monospace;
  text-align: center;
  font-weight:regular;
  font-size: 12px;
}

body {
  background: #1c1c1c;

  min-block-size: 100%;
  min-inline-size: 100%;
  box-sizing: border-box;
  display: grid;
  place-content: center;
  font-family: Helvetica;
  font-size: min(200%, 5vmin);
}
p {
  font-family: Helvetica;
  }

html {
  block-size: 100%;
  inline-size: 100%;
}
* {
  padding: 0;
  margin: 0;
  box-sizing: border-box;
}

.btn {
	width: 190px;
	height: 40px;
	border: none;
	border-radius: 15px;
	font-size: 24px;
	font-weight: 600;
	text-decoration: none;
	color: #1c1c1c;
	background-color: #808080;
	box-shadow: 0 4px 6px rgb(105 148 171/ 40%), 0 1px 3px rgb(0 0 0 / 8%);
	cursor: pointer;
	user-select: none;
	appearance: none;
	touch-action: manipulation;
	vertical-align: top;
	transition: box-shadow 0.2s;
}

input[type=color]{
	width: 190px;
	height: 40px;
	border: none;
	border-radius: 15px;
	background: none;
}

input[type="color"]::-webkit-color-swatch-wrapper {
	padding: 0;
}
input[type="color"]::-webkit-color-swatch {
	border: solid 2px #fff;
	border-radius: 15px;
  box-shadow: 0 4px 6px rgb(105 148 171/ 40%), 0 1px 3px rgb(0 0 0 / 8%);
}
</style>
  </head>
<body>
<center><a href="/handleDrum"><button class="btn" style="background:@@color_drum@@;" type="submit" name="state">БАРАБАНЫ</button></a></center>
     <br>

 <center><a href="/handleLed"><button class="btn" style="background:@@color_led@@;" type="submit" name="state">СВЕТ</button></a></center>
 <br>
 <br>
<text><p>ВЫБОР ЦВЕТА</p></text>
 <br>
 <form method="post" action="/form" name="pick">
         <center><input style="background:@@color@@;" type="color" name="color" value="@@color@@" onchange="document.forms['pick'].submit();"></center>
         <br>
         <span onclick="document.forms['pick'].submit();"></span>
       </form>
 <br>
 <br>
  <footer>@@uptime@@</footer>
  </body>
 </html>

)=====";
