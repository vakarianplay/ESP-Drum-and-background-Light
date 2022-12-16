#include "motordriver.h"

MotorDriver::MotorDriver(uint8_t aPin, uint8_t bPin)
{
    pinA = aPin;
    pinB = bPin;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void MotorDriver::moveForward(uint8_t speed, uint16_t delayTime)
{
    analogWrite(pinA, 0);
    analogWrite(pinB, speed);

    delay(delayTime);

    stopMotor();
}

void MotorDriver::moveBackward(uint8_t speed, uint16_t delayTime)
{
    analogWrite(pinA, speed);
    analogWrite(pinB, 0);

    delay(delayTime);

    stopMotor();
}

void MotorDriver::stopMotor()
{
    analogWrite(pinA, 0);
    analogWrite(pinB, 0);
}
