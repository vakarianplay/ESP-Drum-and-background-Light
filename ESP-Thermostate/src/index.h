#include <Arduino.h>

const char html[] PROGMEM = R"rawliteral(
<html>
  <body>
    <h1>TEST Control</h1>
    <br>
    <p>Relay 1</p>
    <button id='toggleButton' onclick=sendRequest('toggleLed')>%btnTxt%</button>
    <br>
    <p>Sensor</p>
    <p id='value'>-</p>
    <script>
            function sendRequest(url) {
              var xhttp = new XMLHttpRequest();
              xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  var buttonText = this.responseText;
                  document.getElementById('toggleButton').innerText = buttonText;
                }
              };
              xhttp.open('GET', url, true);
              xhttp.send();
            }
            function updateValue() {
              var xhttp = new XMLHttpRequest();
              xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  document.getElementById('value').innerText = this.responseText;
                }
              };
              xhttp.open('GET', '/readSensor', true);
              xhttp.send();
            }
            setInterval(updateValue, 1000);
          </script>
          </body>
</html>
)rawliteral";
