#ifndef __SYSTEM_STATE_TRACKER__
#define __SYSTEM_STATE_TRACKER__

typedef enum {
    TEMP_FINE,
    TEMP_EXCEEDED
} TempTrackerState;

typedef enum {
    LEVEL_FINE,
    LEVEL_EXCEEDED
} LevelTrackerState;

typedef enum {
    TEMP_MONITOR,
    LEVEL_MONITOR
} ExceptionSource;

class SystemStateTracker{
    public:
        SystemStateTracker();
        void restoreSystem(ExceptionSource restoredMonitor);
        void blockSystem(ExceptionSource exceededMonitor);
        bool isSystemBlocked();

    private:
        TempTrackerState tempState;
        LevelTrackerState levelState;
};

#endif