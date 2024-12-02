#ifndef __CONTAINER_HANDLER_TASK__
#define __CONTAINER_HANDLER_TASK__

#include "task.h"
#include "system_state_tracker.h"
#include "door.h"
#include "light.h"
#include "button.h"
#include "user_detector.h"
#include "screen.h"

typedef enum {
    CONTAINER_ACCEPTING_WASTE,
    CONTAINER_OPEN,
    CONTAINER_CLOSING,
    CONTAINER_DEEP_SLEEP_WORKING,
    CONTAINER_TEMP_EXCEEDED,
    CONTAINER_LEVEL_EXCEEDED,
    CONTAINER_EMPTYING,
    CONTAINER_DEEP_SLEEP_NONWORKING
} ContainerHandlerState;

class ContainerHandlerTask: public Task {
    public:
        ContainerHandlerTask(int period, SystemStateTracker *systemTracker);
        void step(int schedPeriod);

    private:
        void setState(ContainerHandlerState state);
        void goToSleep();
        SystemStateTracker *systemTracker;
        int period;
        int schedSteps;
        int noUserSteps;
        int openSteps;
        int closingSteps;
        int emptyingSteps;
        ContainerHandlerState state;
        Door *door;
        Button *openButton;
        Button *closeButton;
        Screen *userScreen;
        Light *greenLight;
        Light *redLight;
        UserDetector *userDetector;
};

#endif