// typewise-alert.cpp
#include "typewise-alert.h"
#include <iostream>

struct CoolingLimits {
  int lowerLimit;
  int upperLimit;
};

CoolingLimits getCoolingLimits(CoolingType coolingType) {
  switch (coolingType) {
    case CoolingType::PASSIVE_COOLING: return {0, 35};
    case CoolingType::HI_ACTIVE_COOLING: return {0, 45};
    case CoolingType::MED_ACTIVE_COOLING: return {0, 40};
  }
  return {0, 0}; // Default case to prevent warning
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) return BreachType::TOO_LOW;
  if (value > upperLimit) return BreachType::TOO_HIGH;
  return BreachType::NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  CoolingLimits limits = getCoolingLimits(coolingType);
  return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  std::cout << std::hex << header << " : " << static_cast<int>(breachType) << std::endl;
}

void sendToEmail(BreachType breachType) {
  const std::string recipient = "a.b@c.com";
  if (breachType == BreachType::TOO_LOW) {
    std::cout << "To: " << recipient << "\nHi, the temperature is too low\n";
  } else if (breachType == BreachType::TOO_HIGH) {
    std::cout << "To: " << recipient << "\nHi, the temperature is too high\n";
  }
}

using AlertFunction = void(*)(BreachType);

void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  
  // Select alert function based on target
  AlertFunction alertFunction = nullptr;
  if (alertTarget == AlertTarget::TO_CONTROLLER) {
    alertFunction = sendToController;
  } else if (alertTarget == AlertTarget::TO_EMAIL) {
    alertFunction = sendToEmail;
  }
  
  // Dispatch alert
  if (alertFunction) {
    alertFunction(breachType);
  }
}
