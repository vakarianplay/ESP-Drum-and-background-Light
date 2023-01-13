![alt text](https://img.shields.io/badge/Chip-ESP8266-blue?style=for-the-badge&logo=Espressif) ![alt text](https://img.shields.io/badge/Chip-ESP32-blue?style=for-the-badge&logo=Espressif)

![alt text](https://img.shields.io/badge/Core-PlatformIO-blue?style=flat-square)


# Visualizer for drumkit and RGB led strip

Project of controller for RGP led strip for drumkit with web interface and cURL control.

**https://github.com/vakarianplay/ESP-Projects/tree/main/ESP-Drum-and-Light**

![alt text](https://github.com/vakarianplay/readmepic/blob/main/drum_light.jpg)

***

# Led breathing interface

Async webinterface for control breathing RGB led modes

**https://github.com/vakarianplay/ESP-Projects/tree/main/ESP-Led-breathing**

![alt text](https://github.com/vakarianplay/readmepic/blob/main/breath.jpg)

***


# Sonoff cURL switch
Light-weight firmware for Sonoff Basic relay with http GET requests

**https://github.com/vakarianplay/ESP-Projects/tree/main/sonoff**

***

# ESP Weather station
Weather station on SSD1306 oled display. Weather data gets from wttr.in and narodmon.ru

**https://github.com/vakarianplay/ESP-Projects/tree/main/ESP-Weather%20Station**

***


### This repository using PlatformIO.

Config for project:
```
[env:d1_mini_lite]
platform = espressif8266
board = d1_mini_lite
framework = arduino
upload_speed = 115200
upload_port = %your_com_port%
lib_deps = %place_libs_here%
```

### Fully compatible with other platforms based on ESP8266 and ESP32.

If using ESP32 need include library `ESPWifi.h` and `ESPWebServer.h`
