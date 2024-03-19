#include <Arduino.h>
#include "CG_RadSens.h"
#include <Wire.h>
#include <GyverOLED.h>

class RadInterface
{
public:
    RadInterface(uint8_t slcPin, uint8_t sdaPin, uint16_t sens);
    String getStatString();
    String getDynString();
    String getImpString();

    void tick();
    // void displayInfo(String ssid, String ip);

    bool isRadConnect();


private:

  GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
  CG_RadSens radSens;

  void initDisp(uint8_t slcPin, uint8_t sdaPin);
  void initRadSens(uint16_t sens);
  void displayData();



  float dynval;
  float statval;
  uint32_t impval;
  uint32_t pulsesPrev;
};
