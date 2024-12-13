#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Preferences.h>
#include "datagrabber.h"
#include <Arduino.h>

const char* ssid = "roof";
const char* password = "12345618";

unsigned long previousMillis = 0;
const long interval = 3000; 

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80);
Preferences preferences;
DataGrabber dataGrabber;

// WiFiClient client;
// HTTPClient http;


const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP Settings</title>
    <style>
        body {
            font-family: sans-serif;
            margin: 20px;
            background-color: #f4f4f4; /* Light gray background */
        }
        h1 {
            color: #333; /* Dark gray heading */
            text-align: center;
        }
        form {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            background-color: #fff; /* White form background */
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1); /* Subtle shadow */
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #555; /* Darker gray labels */
        }
        input[type="text"],
        input[type="number"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 3px;
            box-sizing: border-box;
        }
        input[type="submit"] {
            background-color: #4CAF50; /* Green button */
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 3px;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #45a049; /* Darker green on hover */
        }

    </style>
</head>
<body>
    <h1>ESP MAX7219 LED Scrolling Text Settings</h1>
    <form method="POST" action="/save">
        <label for="streamingUrl">Streaming URL:</label>
        <input type="text" id="streamingUrl" name="streamingUrl" value="{stream}"><br>
        <label for="scrollingSpeed">Scrolling Speed:</label>
        <input type="number" id="scrollingSpeed" name="scrollingSpeed" value="{speed}"><br>

        <input type="submit" value="💾 Save and Reboot">
    </form>
</body>
</html>




)=====";