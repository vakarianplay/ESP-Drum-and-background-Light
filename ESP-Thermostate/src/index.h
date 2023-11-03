#include <Arduino.h>

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style type="text/css">
.button {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
</style>
<body style="background-color: #f9e79f ">
<center>
<div>
<h1>ESP THERMOSTATE</h1>
  <button class="button" id="state1" onclick="toggle1()">LED ON</button>
  <button class="button" id="state2" onclick="toggle2()">LED OFF</button><BR>
</div>
 <br>
<div><h2>
  Temp(C): <span id="temp_val">0</span><br><br>
  Humidity(%): <span id="hum_val">NA</span>
</h2>
</div>
<script>

function toggle1() 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if (this.responseText == "0") {
      document.getElementById("state1").innerHTML = "RELAY1 OFF";
      } else
        document.getElementById("state1").innerHTML = "RELAY1 ON";
    }
  };
  xhttp.open("GET", "toggleRelay1", true);
  xhttp.send();
}

function toggle2() 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if (this.responseText == "0") {
      document.getElementById("state2").innerHTML = "RELAY2 OFF";
      } else
        document.getElementById("state2").innerHTML = "RELAY2 ON";
    }
  };
  xhttp.open("GET", "toggleRelay2", true);
  xhttp.send();
}

function getRelay1() 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if (this.responseText == "0") {
      document.getElementById("state1").innerHTML = "RELAY1 OFF";
      } else
        document.getElementById("state1").innerHTML = "RELAY1 ON";
    }
  };
  xhttp.open("GET", "st1", true);
  xhttp.send();
}

function getRelay2() 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if (this.responseText == "0") {
      document.getElementById("state2").innerHTML = "RELAY2 OFF";
      } else
        document.getElementById("state2").innerHTML = "RELAY2 ON";
    }
  };
  xhttp.open("GET", "st2", true);
  xhttp.send();
}

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temp_val").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "readTemp", true);
  xhttp.send();
}

setInterval(function() 
{
  getData();
  getRelay1();
  getRelay2();
}, 2000); 

document.addEventListener("DOMContentLoaded", function() {
  getData();
  getRelay1();
  getRelay2();
});


</script>
</center>
</body>
</html>
)=====";