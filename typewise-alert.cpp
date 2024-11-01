#include "typewise-alert.h"
#include <stdio.h>
#include <memory>  // Include this for std::unique_ptr and std::make_unique
#include <unordered_map>


// Define temperature limits per cooling type
struct TemperatureLimits {
  double lowerLimit;
  double upperLimit;
};

const std::unordered_map<CoolingType, TemperatureLimits> coolingLimits = {
  {CoolingType::PASSIVE_COOLING, {0, 35}},
  {CoolingType::HI_ACTIVE_COOLING, {0, 45}},
  {CoolingType::MED_ACTIVE_COOLING, {0, 40}}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) {
    return BreachType::TOO_LOW;
  }
  if (value > upperLimit) {
    return BreachType::TOO_HIGH;
  }
  return BreachType::NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  auto limits = coolingLimits.at(coolingType);
  return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void ControllerAlertHandler::sendAlert(BreachType breachType) const {
  const unsigned short header = 0xfeed;
  std::cout << std::hex << header << " : " << static_cast<int>(breachType) << std::endl;
}

void EmailAlertHandler::sendAlert(BreachType breachType) const {
  const std::string recipient = "a.b@c.com";
  if (breachType == BreachType::TOO_LOW) {
    std::cout << "To: " << recipient << "\nHi, the temperature is too low\n";
  } else if (breachType == BreachType::TOO_HIGH) {
    std::cout << "To: " << recipient << "\nHi, the temperature is too high\n";
  }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  std::unique_ptr<AlertHandler> alertHandler;
  if (alertTarget == AlertTarget::TO_CONTROLLER) {
    alertHandler = std::make_unique<ControllerAlertHandler>();
  } else if (alertTarget == AlertTarget::TO_EMAIL) {
    alertHandler = std::make_unique<EmailAlertHandler>();
  }

  if (alertHandler) {
    alertHandler->sendAlert(breachType);
  }
}
