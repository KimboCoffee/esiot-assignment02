#ifndef __TASK__
#define __TASK__

class Task {
    public:
        virtual void step(long schedPeriod) = 0;
};

#endif