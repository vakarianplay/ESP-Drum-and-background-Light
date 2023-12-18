## Firmware for Sonoff Basic R2 for control by cURL.

Lightweight firmware with minimalistic web server.
Develop for swith relay via crontab with cURL.

--------------------

* Web page

` curl http://SONOFF_IP/`

* Get state

` curl http://SONOFF_IP/st`

* Switch on

` curl http://SONOFF_IP/on`

* Switch off

` curl http://SONOFF_IP/off`

* System information (json format)

` curl http://SONOFF_IP/dev`

* OTA update

` curl http://SONOFF_IP/firmware`
