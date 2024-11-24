#ifndef __PIR_USER_DETECTOR__
#define __PIR_USER_DETECTOR__

#include "user_detector.h"

class PIRUserDetector : public UserDetector {
    public:
        PIRUserDetector(int pin);
        bool isDetecting();

    private:
        int pin;
};

#endif