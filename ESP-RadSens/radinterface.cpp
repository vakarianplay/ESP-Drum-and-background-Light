#include "radinterface.h"

RadInterface::RadInterface(uint8_t slcPin, uint8_t sdaPin, uint16_t sens)
{
  initDisp(slcPin, sdaPin);
  initRadSens(sens);

}

void RadInterface::initRadSens(uint16_t sens)
{
  radSens.init();
  radSens.setSensitivity(sens);
}

void RadInterface::initDisp(uint8_t slcPin, uint8_t sdaPin)
{
  oled.init(slcPin, sdaPin);
  oled.flipV(1);
  oled.flipH(1);
  oled.clear();
  oled.setScale(2);
  oled.print("CG_RadSens");
  oled.setCursor(0, 5);
  // oled.print(radSens.getFirmwareVersion());
  // delay(3000);
  oled.clear();
}

void RadInterface::tick()
{
  dynval = radSens.getRadIntensyDynamic();
  statval = radSens.getRadIntensyStatic();
  impval = radSens.getNumberOfPulses();
  // oled.clear();
  displayData();
}

void RadInterface::displayData()
{
  String dynint = "Дин: ";
  dynint += dynval;
  String statint = "Ст:  ";
  statint += statval;
  String nimp = "Имп: ";
  nimp += impval;
  oled.setCursor(0, 1);
  oled.print(dynint);
  oled.setCursor(0, 3);
  oled.print(statint);
  oled.setCursor(0, 5);
  oled.print(nimp);
}

// void RadInterface::displayInfo(String ssid, String ip)
// {
//   String wifi = "WiFi ВКЛ " + ssid;
//   String page = ip;
//   String ver = "Версия: 0.2. CG_вер " + String(radSens.getFirmwareVersion());
//   oled.setCursor(0, 1);
//   oled.print(wifi);
//   oled.setCursor(0, 3);
//   oled.print(page);
//   oled.setCursor(0, 5);
//   oled.print(ver);
// }

bool RadInterface::isRadConnect()
{
  return true;
}


String RadInterface::getStatString()
{
  String sensorValue = String(radSens.getRadIntensyStatic());
  return sensorValue;
}

String RadInterface::getDynString()
{
  String sensorValue = String(radSens.getRadIntensyDynamic());
  return sensorValue;
}

String RadInterface::getImpString()
{
  String sensorValue = String(radSens.getNumberOfPulses());
  return sensorValue;
}
