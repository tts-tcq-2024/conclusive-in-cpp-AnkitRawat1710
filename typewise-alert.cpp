#include "typewise-alert.h"
#include <iostream>
#include <memory> // Include memory for std::unique_ptr

// Implement different breach classifiers
class PassiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 35);
  }
};

class HiActiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 45);
  }
};

class MedActiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 40);
  }
};

// Implement different alert mechanisms
class ControllerAlert : public IAlert {
public:
  void send(BreachType breachType) const override {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<int>(breachType) << "\n";
  }
};

class EmailAlert : public IAlert {
public:
  void send(BreachType breachType) const override {
    const std::string recipient = "a.b@c.com";
    if (breachType == BreachType::TOO_LOW) {
      std::cout << "To: " << recipient << "\n";
      std::cout << "Hi, the temperature is too low\n";
    } else if (breachType == BreachType::TOO_HIGH) {
      std::cout << "To: " << recipient << "\n";
      std::cout << "Hi, the temperature is too high\n";
    }
  }
};

// Factory function to create breach classifiers
std::unique_ptr<IBreachClassifier> createBreachClassifier(CoolingType coolingType) {
  switch(coolingType) {
    case CoolingType::PASSIVE_COOLING: return std::make_unique<PassiveCoolingBreachClassifier>();
    case CoolingType::HI_ACTIVE_COOLING: return std::make_unique<HiActiveCoolingBreachClassifier>();
    case CoolingType::MED_ACTIVE_COOLING: return std::make_unique<MedActiveCoolingBreachClassifier>();
    default: throw std::invalid_argument("Unknown CoolingType");
  }
}

// Factory function to create alert types
std::unique_ptr<IAlert> createAlert(AlertTarget alertTarget) {
  switch(alertTarget) {
    case AlertTarget::TO_CONTROLLER: return std::make_unique<ControllerAlert>();
    case AlertTarget::TO_EMAIL: return std::make_unique<EmailAlert>();
    default: throw std::invalid_argument("Unknown AlertTarget");
  }
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) {
    return BreachType::TOO_LOW;
  }
  if (value > upperLimit) {
    return BreachType::TOO_HIGH;
  }
  return BreachType::NORMAL;
}

void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
  auto breachClassifier = createBreachClassifier(batteryChar.coolingType);
  auto alert = createAlert(alertTarget);

  BreachType breachType = breachClassifier->classify(temperatureInC);
  alert->send(breachType);
}

