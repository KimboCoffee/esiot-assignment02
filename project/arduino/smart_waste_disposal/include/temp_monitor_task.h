#ifndef __TEMP_MONITOR_TASK__
#define __TEMP_MONITOR_TASK__

#include "task.h"
#include "temperature_sensor.h"
#include "system_state_tracker.h"

#define ALERT_TIME_THRESHOLD 1000
#define TEMP_THRESHOLD 30.0

typedef enum {
    TEMP_MONITOR_OK,
    TEMP_MONITOR_ALERT,
    TEMP_MONITOR_NOT_OK
} TempMonitorState;

class TempMonitorTask: public Task {
    public:
        TempMonitorTask(int period, SystemStateTracker *systemTracker);
        void step(int schedPeriod);
        float getLastMeasure();
        void setState(TempMonitorState state);

    private:
        int period;
        TempMonitorState state;
        TemperatureSensor *sensor;
        float lastMeasure;
        int schedSteps;
        int alertSteps;
        SystemStateTracker *systemTracker;
};

#endif