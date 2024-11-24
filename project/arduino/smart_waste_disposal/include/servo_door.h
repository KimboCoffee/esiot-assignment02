#ifndef __SERVO_DOOR__
#define __SERVO_DOOR__

#include <ServoTimer2.h>
#include "door.h"

class ServoDoor : public Door {
    public:
        ServoDoor(int pin);
        void lock();
        void unlock();
        void openForInsertion();
        void close();
        void openForEmptying();

    private:
        ServoTimer2 *motor;
        int pin;
};

#endif