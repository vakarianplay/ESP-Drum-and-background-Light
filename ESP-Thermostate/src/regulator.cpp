#include "regulator.h"

Regulator::Regulator(uint8_t aPin, uint8_t bPin)
{
    relayT = aPin;
    relayH = bPin;
    pinMode(relayT, OUTPUT);
    pinMode(relayH, OUTPUT);
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


String Regulator::getTempString()
{
  String sensorValue = String(analogRead(A0));
  return sensorValue;
}

String Regulator::getHumString()
{
  String sensorValue = String(analogRead(A0) * 0.4);
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
