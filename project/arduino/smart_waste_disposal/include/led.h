#ifndef __LED__
#define __LED__

#include "light.h"

class Led : public Light {
    public:
        Led(int pin);
        void turn();
        bool isOn();

    private:
        int pin;
        bool state;
};

#endif