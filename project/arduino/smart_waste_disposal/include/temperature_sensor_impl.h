#ifndef __TEMPERATURE_SENSOR_IMPL__
#define __TEMPERATURE_SENSOR_IMPL__

#include "temperature_sensor.h"

class TemperatureSensorImpl : public TemperatureSensor {
    public:
        TemperatureSensorImpl(int pin);

        float getTemp();

    private:
        int pin;
};

#endif