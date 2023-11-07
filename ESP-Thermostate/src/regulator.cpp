#include "regulator.h"

Regulator::Regulator(uint8_t aPin, uint8_t bPin)
{
    relayT = aPin;
    relayH = bPin;
    pinMode(relayT, OUTPUT);
    pinMode(relayH, OUTPUT);

    tempSet = 30.10;
    humSet = 10.30;
}

void Regulator::tick() {
  tempValue = analogRead(A0);
  humValue = analogRead(A0) * 0.4;
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
