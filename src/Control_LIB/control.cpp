#include "control.h"

void Control::begin(uint8_t pin)
{
    pinNumber = pin;
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, HIGH);
    isTurnOn = false;
};

void Control::turnOn()
{
    if(!isTurnOn) {
        digitalWrite(pinNumber, LOW);
        isTurnOn = true;
    }
};

void Control::turnOff()
{
    if(isTurnOn) {
    digitalWrite(pinNumber,HIGH);
    isTurnOn = false;
    }
};