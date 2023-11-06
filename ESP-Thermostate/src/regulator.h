#include "Arduino.h"

class Regulator
{
public:
    Regulator(uint8_t aPin, uint8_t bPin);
    String getTempString();
    String getHumString();

private:
    uint8_t relayT;
    uint8_t relayH;
    int16_t temperature;
    int16_t humidity;
};
