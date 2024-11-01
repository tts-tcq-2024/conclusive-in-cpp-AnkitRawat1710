#include "typewise-alert.h"
#include <iostream>
#include <memory>
#include <map>
#include <stdexcept>

// Breach Classification Implementation
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) return TOO_LOW;
  if (value > upperLimit) return TOO_HIGH;
  return NORMAL;
}

// Passive Cooling Classifier
class PassiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 35);
  }
};

// High Active Cooling Classifier
class HiActiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 45);
  }
};

// Medium Active Cooling Classifier
class MedActiveCoolingBreachClassifier : public IBreachClassifier {
public:
  BreachType classify(double temperatureInC) const override {
    return inferBreach(temperatureInC, 0, 40);
  }
};

// Factory for Breach Classifiers
std::unique_ptr<IBreachClassifier> createBreachClassifier(CoolingType coolingType) {
  static const std::map<CoolingType, std::function<std::unique_ptr<IBreachClassifier>()>> classifierMap = {
    { PASSIVE_COOLING, []() { return std::make_unique<PassiveCoolingBreachClassifier>(); } },
    { HI_ACTIVE_COOLING, []() { return std::make_unique<HiActiveCoolingBreachClassifier>(); } },
    { MED_ACTIVE_COOLING, []() { return std::make_unique<MedActiveCoolingBreachClassifier>(); } }
  };
  
  auto it = classifierMap.find(coolingType);
  if (it != classifierMap.end()) {
    return it->second();
  }
  throw std::invalid_argument("Unknown CoolingType");
}

// Alert Implementations
class ControllerAlert : public IAlert {
public:
  void send(BreachType breachType) const override {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << breachType << std::endl;
  }
};

class EmailAlert : public IAlert {
public:
  void send(BreachType breachType) const override {
    const std::string recepient = "a.b@c.com";
    if (breachType == TOO_LOW) {
      std::cout << "To: " << recepient << "\nHi, the temperature is too low\n";
    } else if (breachType == TOO_HIGH) {
      std::cout << "To: " << recepient << "\nHi, the temperature is too high\n";
    }
  }
};

// Factory for Alerts
std::unique_ptr<IAlert> createAlert(AlertTarget alertTarget) {
  static const std::map<AlertTarget, std::function<std::unique_ptr<IAlert>()>> alertMap = {
    { TO_CONTROLLER, []() { return std::make_unique<ControllerAlert>(); } },
    { TO_EMAIL, []() { return std::make_unique<EmailAlert>(); } }
  };
  
  auto it = alertMap.find(alertTarget);
  if (it != alertMap.end()) {
    return it->second();
  }
  throw std::invalid_argument("Unknown AlertTarget");
}

// Main checkAndAlert function
void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
  auto breachClassifier = createBreachClassifier(batteryChar.coolingType);
  BreachType breachType = breachClassifier->classify(temperatureInC);
  
  auto alert = createAlert(alertTarget);
  alert->send(breachType);
}

