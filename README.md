![alt text](https://img.shields.io/badge/WeMos%20D1%20mini-ESP8266-blue)

![alt text](https://img.shields.io/badge/Library-ESP8266WiFi-228B22) ![alt text](https://img.shields.io/badge/Library-ESP8266WebServer-228B22) ![alt text](https://img.shields.io/badge/Library-Uptime%20Library-228B22) ![alt text](https://img.shields.io/badge/Library-Streaming-228B22)

# ESP8266 (WeMos D1 mini)
## Visualizer for drumkit and RGB led strip controller with web interface



Web interface page on CodePen: https://codepen.io/uliosulio/pen/zYPrJqw

Wiki: https://github.com/vakarianplay/ESP-Drum-and-background-Light/wiki

![](https://istarik.ru/uploads/images/00/00/01/2018/11/04/38c9d6.png)

***

### This repository using PlatformIO.

Config for project:
```
[env:d1_mini_lite]
platform = espressif8266
board = d1_mini_lite
framework = arduino
upload_speed = 115200
upload_port = COM7
lib_deps = mikalhart/Streaming@^1.0.0, lib/Uptime-Library-1.0.0
```
