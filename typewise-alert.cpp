#include "typewise-alert.h"
#include <stdio.h>
#include <map>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if(value < lowerLimit) return TOO_LOW;
    if(value > upperLimit) return TOO_HIGH;
    return NORMAL;
}

std::pair<int, int> getCoolingLimits(CoolingType coolingType) {
    static const std::map<CoolingType, std::pair<int, int>> coolingLimits = {
        {PASSIVE_COOLING, {0, 35}},
        {HI_ACTIVE_COOLING, {0, 45}},
        {MED_ACTIVE_COOLING, {0, 40}}
    };
    return coolingLimits.at(coolingType);
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    auto [lowerLimit, upperLimit] = getCoolingLimits(coolingType);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    switch(alertTarget) {
        case TO_CONTROLLER:
            sendToController(breachType);
            break;
        case TO_EMAIL:
            sendToEmail(breachType);
            break;
    }
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    switch(breachType) {
        case TOO_LOW:
            printf("To: %s\nHi, the temperature is too low\n", recipient);
            break;
        case TOO_HIGH:
            printf("To: %s\nHi, the temperature is too high\n", recipient);
            break;
        case NORMAL:
            break;
    }
}

