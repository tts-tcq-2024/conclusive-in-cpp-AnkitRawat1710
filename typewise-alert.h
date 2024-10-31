#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

// Breach types enumeration
typedef enum {
    TOO_LOW,
    TOO_HIGH,
    NORMAL
} BreachType;

// Cooling types enumeration
typedef enum {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
} CoolingType;

// Battery character structure
typedef struct {
    CoolingType coolingType;
} BatteryCharacter;

// Function declarations
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit);
void checkAndAlert(BatteryCharacter batteryChar, double temperatureInC);
void sendAlert(BreachType breachType);

#endif // TYPEWISE_ALERT_H
