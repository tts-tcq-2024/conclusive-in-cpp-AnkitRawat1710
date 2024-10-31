#include "typewise-alert.h"
#include <stdio.h>

// Function to classify the temperature breach
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    } else if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

// Function to get cooling limits based on the cooling type
void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit) {
    switch (coolingType) {
        case PASSIVE_COOLING:
            *lowerLimit = 0;
            *upperLimit = 35;
            break;
        case HI_ACTIVE_COOLING:
            *lowerLimit = 0;
            *upperLimit = 45;
            break;
        case MED_ACTIVE_COOLING:
            *lowerLimit = 0;
            *upperLimit = 40;
            break;
        default:
            *lowerLimit = 0;
            *upperLimit = 0;
            break;
    }
}

// Function to check the temperature and send alerts accordingly
void checkAndAlert(BatteryCharacter batteryChar, double temperatureInC) {
    int lowerLimit, upperLimit;
    getCoolingLimits(batteryChar.coolingType, &lowerLimit, &upperLimit);
    BreachType breachType = inferBreach(temperatureInC, lowerLimit, upperLimit);
    sendAlert(breachType);
}

// Function to send alerts based on the breach type
void sendAlert(BreachType breachType) {
    switch (breachType) {
        case TOO_LOW:
            printf("Alert: Temperature too low!\n");
            // Here you can implement sending to email/controller
            break;
        case TOO_HIGH:
            printf("Alert: Temperature too high!\n");
            // Here you can implement sending to email/controller
            break;
        case NORMAL:
            printf("Temperature is normal.\n");
            break;
        default:
            break;
    }
}


