#include "Arduino.h"

class Regulator
{
public:
    Regulator(uint8_t aPin, uint8_t bPin);
    String getTempString();
    String getHumString();

    String getTempSetString();
    String getHumSetString();
    String getHysteresis();

    void setValues(float tempval_, float humval_, float hystval_);

    bool isRegulator();

private:

    bool regulatorState = false;

    uint8_t relayT;
    uint8_t relayH;
    float tempValue;
    float humValue;

    float tempSet;
    float humSet;
    float hysteresis = 5.3;
};
