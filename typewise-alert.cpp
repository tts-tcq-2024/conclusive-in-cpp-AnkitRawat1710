#include "typewise-alert.h"
#include <stdio.h>

// Helper function to get limits based on cooling type
void getCoolingLimits(CoolingType coolingType, double &lowerLimit, double &upperLimit) {
    switch(coolingType) {
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
            lowerLimit = 0;
            upperLimit = 0; // Default case to avoid uninitialized variable
            break;
    }
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    double lowerLimit, upperLimit;
    getCoolingLimits(coolingType, lowerLimit, upperLimit);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void alertToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void alertByEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature is too low\n");
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature is too high\n");
    }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    if (alertTarget == TO_CONTROLLER) {
        alertToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        alertByEmail(breachType);
    }
}

