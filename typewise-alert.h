#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

// Include necessary standard libraries
#include <iostream>
#include <string>

// Forward declarations or includes for AlertTarget and BatteryCharacter
enum AlertTarget {
    TO_EMAIL,
    TO_CONSOLE
};

struct BatteryCharacter {
    CoolingType coolingType; // Assuming CoolingType is defined elsewhere
    std::string batteryId;   // Assuming batteryId is of type string
};

// Function declarations
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
// Other function declarations...

#endif // TYPEWISE_ALERT_H
