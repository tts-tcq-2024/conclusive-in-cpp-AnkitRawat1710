#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

enum BreachType {
    TOO_LOW,
    TOO_HIGH,
    NORMAL
};

enum CoolingType {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
};

struct BatteryCharacter {
    CoolingType coolingType; // Assuming CoolingType is defined elsewhere
};

// Function declarations
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

#endif // TYPEWISE_ALERT_H

