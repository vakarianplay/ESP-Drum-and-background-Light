#include "regulator.h"

Regulator::Regulator(uint8_t aPin, uint8_t bPin)
{
    relayT = aPin;
    relayH = bPin;
    pinMode(relayT, OUTPUT);
    pinMode(relayH, OUTPUT);
}


// void Regulator::startMotor()
// {
//     moveForward(255, 150);
// }

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
