#ifndef __SONAR_LEVEL_GAUGE__
#define __SONAR_LEVEL_GAUGE__

#include "level_gauge.h"

class SonarLevelGauge : public LevelGauge {
    public:
        SonarLevelGauge(int trigPin, int echoPin);
        float getFillingPercentage();

    private:
        float getDistance();
        int trigPin;
        int echoPin;
        float baseDist;
};

#endif