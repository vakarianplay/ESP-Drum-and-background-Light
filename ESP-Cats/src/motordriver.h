#include "Arduino.h"

class MotorDriver
{
public:
    MotorDriver(uint8_t aPin, uint8_t bPin);
    void moveForward(uint8_t speed, uint16_t delayTime);
    void moveBackward(uint8_t speed, uint16_t delayTime);
    void stopMotor();
    void startMotor();

private:
    uint8_t pinA;
    uint8_t pinB;
};
