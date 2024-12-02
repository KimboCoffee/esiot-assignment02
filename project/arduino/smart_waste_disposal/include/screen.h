#ifndef __SCREEN__
#define __SCREEN__

class Screen {
    public:
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        virtual void clear() = 0;
        virtual void println(int row, String msg) = 0;
};

#endif