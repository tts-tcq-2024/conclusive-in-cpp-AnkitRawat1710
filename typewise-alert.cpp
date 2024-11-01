#include "typewise-alert.h"
#include <iostream>
#include <memory>

// Determine the breach type based on cooling type and temperature
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;
    
    switch (coolingType) {
        case PASSIVE_COOLING:
            upperLimit = 35;
            break;
        case HI_ACTIVE_COOLING:
            upperLimit = 45;
            break;
        case MED_ACTIVE_COOLING:
            upperLimit = 40;
            break;
    }

    if (temperatureInC < lowerLimit) {
        return TOO_LOW;
    }
    if (temperatureInC > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

// Factory function to get the correct alert handler based on AlertTarget
std::unique_ptr<AlertHandler> getAlertHandler(AlertTarget alertTarget) {
    if (alertTarget == TO_CONTROLLER) {
        return std::make_unique<ControllerAlertHandler>();
    } else if (alertTarget == TO_EMAIL) {
        return std::make_unique<EmailAlertHandler>();
    }
    return nullptr;
}

// Check and alert based on temperature breach type
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    auto alertHandler = getAlertHandler(alertTarget);
    if (alertHandler) {
        alertHandler->sendAlert(breachType);
    }
}

// Implementation of ControllerAlertHandler's sendAlert
void ControllerAlertHandler::sendAlert(BreachType breachType) const {
    const int header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<int>(breachType) << std::endl;
}

// Implementation of EmailAlertHandler's sendAlert
void EmailAlertHandler::sendAlert(BreachType breachType) const {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too low\n";
    } else if (breachType == TOO_HIGH) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too high\n";
    }
}

