// typewise-alert.cpp

#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

void getCoolingLimits(CoolingType coolingType, int& lowerLimit, int& upperLimit) {
    switch (coolingType) {
        case PASSIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 35;
            break;
        case HI_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 45;
            break;
        case MED_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 40;
            break;
        default:
            // Handle unexpected cooling types
            lowerLimit = 0;
            upperLimit = 0; // Or set to some default error value
            break;
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit, upperLimit;
    getCoolingLimits(coolingType, lowerLimit, upperLimit);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// ... rest of the code remains unchanged
