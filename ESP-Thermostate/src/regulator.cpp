#include "regulator.h"

Regulator::Regulator(uint8_t aPin, uint8_t bPin)
{
    relayT = aPin;
    relayH = bPin;
    sht.begin(4,5);
    pinMode(relayT, OUTPUT);
    pinMode(relayH, OUTPUT);

    tempSet = 25.10;
    humSet = 35.80;
}

void Regulator::tick() {
  sht.read();
  tempValue = sht.getTemperature();
  humValue = sht.getHumidity();
  if (regulatorState){
    tempRelay();
    humRelay();
  }
}

bool Regulator::isRegulator()
{
  return regulatorState;
}

void Regulator::setValues(float tempval_, float humval_, float hystval_)
{
  tempSet = tempval_;
  humSet = humval_;
  hysteresis = hystval_;
}

void Regulator::toggleRegulator()
{
  regulatorState = !regulatorState;
}

void Regulator::tempRelay(){
  if (tempValue < tempSet) {
    digitalWrite(relayT, 1);
  } else {
    digitalWrite(relayT, 0);
  }
}

void Regulator::humRelay(){
  if (humValue < humSet) {
    digitalWrite(relayH, 1);
  } else {
    digitalWrite(relayH, 0);
  }
}

String Regulator::getTempString()
{
  // sht.read();
  String sensorValue = String(sht.getTemperature());
  return sensorValue;
}

String Regulator::getHumString()
{
  // sht.read();
  String sensorValue = String(sht.getHumidity());
  return sensorValue;
}

String Regulator::getTempSetString()
{
  return String(tempSet);
}

String Regulator::getHumSetString()
{
  return String(humSet);
}

String Regulator::getHysteresis()
{
  return String(hysteresis);
}
