#include "typewise-alert.h"
#include <stdio.h>
#include <utility> // Include for std::pair

// Define limits in an array or structure to eliminate branching
const std::pair<int, int> coolingLimits[] = {
    {0, 35},  // PASSIVE_COOLING
    {0, 45},  // HI_ACTIVE_COOLING
    {0, 40}   // MED_ACTIVE_COOLING
};

std::pair<int, int> getCoolingLimits(CoolingType coolingType) {
    if (coolingType < PASSIVE_COOLING || coolingType > MED_ACTIVE_COOLING) {
        return {0, 0}; // Return a default value for invalid types
    }
    return coolingLimits[coolingType];
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    auto [lowerLimit, upperLimit] = getCoolingLimits(coolingType);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    switch (alertTarget) {
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
    
    const char* message = getBreachMessage(breachType);
    if (message) {
        printf("To: %s\n", recipient);
        printf("%s\n", message);
    }
}

const char* getBreachMessage(BreachType breachType) {
    if (breachType == TOO_LOW) {
        return "Hi, the temperature is too low";
    } else if (breachType == TOO_HIGH) {
        return "Hi, the temperature is too high";
    }
    return nullptr; // Return nullptr for NORMAL or if there's no breach
}

