## Firmware for Sonoff Basic R2 for control by cURL.

Lightweight firmware with minimalistic web server.
Develop for swith relay via crontab with cURL.

--------------------

**CLI client written by Golang is available here**

* Repository: https://github.com/vakarianplay/GoClients/tree/main/RelayClient
* Releases for Windows and Linux https://github.com/vakarianplay/GoRelayClient/releases/tag/v1

--------------------

* Web page

` curl http://SONOFF_IP/`

* Get state

` curl http://SONOFF_IP/st`

* Switch on

` curl http://SONOFF_IP/on`

* Switch off

` curl http://SONOFF_IP/off`

* Toggle state

` curl http://SONOFF_IP/toggleRelay1`

* System information (json format)

` curl http://SONOFF_IP/dev`

* OTA update

` curl http://SONOFF_IP/firmware`
