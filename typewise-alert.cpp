// typewise-alert.cpp
#include "typewise-alert.h"
#include <iostream>
#include <memory>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0, upperLimit = 0;
    switch (coolingType) {
        case PASSIVE_COOLING: lowerLimit = 0; upperLimit = 35; break;
        case HI_ACTIVE_COOLING: lowerLimit = 0; upperLimit = 45; break;
        case MED_ACTIVE_COOLING: lowerLimit = 0; upperLimit = 40; break;
    }
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    std::unique_ptr<AlertHandler> alertHandler;
    if (alertTarget == TO_CONTROLLER) {
        alertHandler = std::make_unique<ControllerAlertHandler>();
    } else if (alertTarget == TO_EMAIL) {
        alertHandler = std::make_unique<EmailAlertHandler>();
    }

    if (alertHandler) {
        alertHandler->sendAlert(breachType);
    }
}

void ControllerAlertHandler::sendAlert(BreachType breachType) const {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<int>(breachType) << std::endl;
}

void EmailAlertHandler::sendAlert(BreachType breachType) const {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too low\n";
    } else if (breachType == TOO_HIGH) {
        std::cout << "To: " << recipient << "\nHi, the temperature is too high\n";
    }
}
