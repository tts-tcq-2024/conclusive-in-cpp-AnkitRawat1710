#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <iostream>
#include <string>

// Define CoolingType enumeration
enum CoolingType {
    AIR_COOLING,
    WATER_COOLING,
    NONE
};

// Define BreachType enumeration
enum BreachType {
    NO_BREACH,
    LOW_BREACH,
    HIGH_BREACH
};

// Define AlertTarget enumeration
enum AlertTarget {
    TO_EMAIL,
    TO_CONTROLLER,
    TO_CONSOLE
};

// Define BatteryCharacter struct
struct BatteryCharacter {
    CoolingType coolingType; 
    std::string batteryId;
};

// Function declarations
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

#endif // TYPEWISE_ALERT_H
