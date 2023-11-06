#include <Arduino.h>

const char webpage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="utf-8" name="viewport" content="width=device-width initial-scale=1">
  <title>ESP Thermostate</title>
  <style type="text/css">


  :root {
    --checkbox-slider-offset: 10000px;
    --checkbox-slider-size: 30px;
    --checkbox-slider-toggle: calc(var(--checkbox-slider-size) * 0.8);
    font-family: Helvetica;
    width: 100%;
    max-width: 100%;
    max-height: 100%;
    overflow: hidden;
  }
    .checkbox-slider {
      font-size: 25pt;
    }

  @supports (--a: 1) {
    input[type="checkbox"].checkbox-slider,
    .checkbox-slider input[type="checkbox"]
    {
      position: relative;
      left: var(--checkbox-slider-offset);
      height: var(--checkbox-slider-size);
      width: var(--checkbox-slider-size);

      &::before, &::after {
        position: absolute;
        content: '';
        display: block;
        cursor: pointer;
        left: calc(var(--checkbox-slider-offset) * -1);
      }

      &::before {
        border-radius: var(--checkbox-slider-size);
        width: calc(var(--checkbox-slider-size) * 2);
        height: var(--checkbox-slider-size);
        background: #aaa;
        transition: background-color 200ms;
      }

      &:checked::before {
        background: #3f729b;
      }

      &::after {
        width: var(--checkbox-slider-toggle);
        height: var(--checkbox-slider-toggle);
        background: #fff;
        top: 50%;
        transform: translateY(-50%) translateX(13%);
        border-radius: var(--checkbox-slider-toggle);
        transition: box-shadow 100ms ease-in-out, transform 100ms ease-in-out;
      }

      &:checked::after {
        box-shadow: 0 2px 5px rgba(0, 0, 0, 0.4);
        transform: translateY(-50%) translateX(133%);
      }
    }

  }
   a.button {
    font-weight: 700;
    color: white;
    text-decoration: none;
    padding: .8em 1em calc(.8em + 3px);
    border-radius: 3px;
    background: #24744c;
    box-shadow: 0 -3px rgb(53,167,110) inset;
    transition: 0.2s;
  }
  a.button:hover { background: rgb(53, 167, 110); }
  a.button:active {
    background: rgb(33,147,90);
    box-shadow: 0 3px rgb(33,147,90) inset;
  }

  .settings-link {
    position:absolute;
     left:0px;
     bottom:0px;
     height:60px;
     width:100%;
  }

  .centralblock {
        position: fixed;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
      }
  </style>
  </head>
  <body>
  <center>
  <div class="centralblock">
  	<div>
  		<h1>ESP THERMOSTATE</h1><br>
  		<p class="checkbox-slider">RELAY 1 <input type="checkbox" onclick="toggle1()" id="fluency" unchecked>
  		<p class="checkbox-slider">RELAY 2 <input type="checkbox" onclick="toggle2()" id="fluency" unchecked>
  	</div>
  	 <br>
  	<div>
  		<h2>
  		  Temp(C): <span id="temp_val">0</span><br><br>
  		  Humidity(%): <span id="hum_val">NA</span>
  		</h2>
  	</div>
  </div>
  <div class="settings-link">
  	<a class="button" href="/handleSettings"><span>&#9881;</span> Settings</a>
  	<p style="font-size:12px;padding: 7px;">Uptime: <span id="uptime_val">NA</span>
  </div>
  <script>

  function toggle1()
  {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == "0") {
          document.getElementById("state1").checked = false;
        // document.getElementById("state1").innerHTML = "RELAY1 OFF";
        } else
          document.getElementById("state1").checked = true;
          // document.getElementById("state1").innerHTML = "RELAY1 ON";
      }
    };
    console.log('Toggle func 1');
    xhttp.open("GET", "toggleRelay1", true);
    xhttp.send();
  }

  function toggle2()
  {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == "0") {
          document.getElementById("state2").checked = false;
        // document.getElementById("state2").innerHTML = "RELAY2 OFF";
        } else
          document.getElementById("state2").checked = true;
          // document.getElementById("state2").innerHTML = "RELAY2 ON";
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
          document.getElementById("state1").checked = false;
        // document.getElementById("state1").innerHTML = "RELAY1 OFF";
        } else
          document.getElementById("state1").checked = true;
          // document.getElementById("state1").innerHTML = "RELAY1 ON";
      }
    };
    console.log('UPD func 1');
    xhttp.open("GET", "st1", true);
    xhttp.send();
  }

  function getRelay2()
  {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == "0") {
          document.getElementById("state2").checked = false;
        // document.getElementById("state2").innerHTML = "RELAY2 OFF";
        } else
          document.getElementById("state2").checked = true;
          // document.getElementById("state2").innerHTML = "RELAY2 ON";
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

  function getHumData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("hum_val").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "readHum", true);
    xhttp.send();
  }

  function getUptime() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("uptime_val").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "readUptime", true);
    xhttp.send();
  }

  setInterval(function()
  {
    getData();
    getHumData();
    getUptime();
    getRelay1();
    getRelay2();
  }, 2000);

  document.addEventListener("DOMContentLoaded", function() {
    getData();
    getHumData();
    getUptime();
    getRelay1();
    getRelay2();
  });


  </script>
  </center>
  </body>
  </html>

)=====";
