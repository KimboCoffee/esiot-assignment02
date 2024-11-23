#ifndef __LIGHT__
#define __LIGHT__

class Light {
    public:
        virtual void turn() = 0;
        virtual bool isOn() = 0;
};

#endif