#include "typewise-alert.h"
#include <iostream>

// Helper function for inferring breach type
BreachType CoolingLimitHandler::inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return BreachType::TOO_LOW;
    if (value > upperLimit) return BreachType::TOO_HIGH;
    return BreachType::NORMAL;
}

// Classifies temperature breach based on cooling type
BreachType CoolingLimitHandler::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    double lowerLimit = 0, upperLimit = 0;
    
    switch (coolingType) {
        case CoolingType::PASSIVE_COOLING:
            upperLimit = 35; break;
        case CoolingType::HI_ACTIVE_COOLING:
            upperLimit = 45; break;
        case CoolingType::MED_ACTIVE_COOLING:
            upperLimit = 40; break;
    }
    
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// Sends alert to controller
void ControllerAlert::sendAlert(BreachType breachType) {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<int>(breachType) << std::endl;
}

// Sends alert via email
void EmailAlert::sendAlert(BreachType breachType) {
    const std::string recipient = "a.b@c.com";
    if (breachType == BreachType::TOO_LOW) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too low\n";
    } else if (breachType == BreachType::TOO_HIGH) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too high\n";
    }
}

// Checks and alerts based on breach type
void checkAndAlert(AlertHandler* alertHandler, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = CoolingLimitHandler::classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    alertHandler->sendAlert(breachType);
}
