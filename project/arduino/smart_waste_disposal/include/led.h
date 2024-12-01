#ifndef __LED__
#define __LED__

#include "light.h"

class Led : public Light {
    public:
        Led(int pin);
        void turnOn();
        void turnOff();
        bool isOn();

    private:
        int pin;
        bool state;
};

#endif