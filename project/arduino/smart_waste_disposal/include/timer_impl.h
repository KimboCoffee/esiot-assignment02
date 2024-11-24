#ifndef __TIMER__
#define __TIMER__

#include <Timer.h>

class TimerImpl {
    public:
        TimerImpl(int period);
        void setPeriod(int period);
        void waitForNextTick();

    private:
        Timer* timer;
        uint32_t period;
};

#endif