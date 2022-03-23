#ifndef CONTROL_h
#define CONTROL_h
#include <Arduino.h>

class Control
{
private:
    uint8_t pinNumber;
    boolean isTurnOn;
    
public:
    void begin(uint8_t pin);
    void turnOn();
    void turnOff();
};

#endif
