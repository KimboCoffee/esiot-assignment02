#ifndef __SERVO_DOOR__
#define __SERVO_DOOR__

#include <ServoTimer2.h>
#include "door.h"

class ServoDoor : public Door {
    public:
        ServoDoor(int pin);
        void openForInsertion();
        void close();
        void openForEmptying();

    private:
        void set(int value);
        ServoTimer2 *motor;
        int pin;
};

#endif