#include "typewise-alert.h"
#include <stdio.h>
#include <memory>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) return TOO_LOW;
  if (value > upperLimit) return TOO_HIGH;
  return NORMAL;
}

// Cooling Strategies
class PassiveCooling : public ICoolingStrategy {
public:
  BreachType classifyTemperature(double temperature) const override {
    return inferBreach(temperature, 0, 35);
  }
};

class HiActiveCooling : public ICoolingStrategy {
public:
  BreachType classifyTemperature(double temperature) const override {
    return inferBreach(temperature, 0, 45);
  }
};

class MedActiveCooling : public ICoolingStrategy {
public:
  BreachType classifyTemperature(double temperature) const override {
    return inferBreach(temperature, 0, 40);
  }
};

// Alert Strategies
class ControllerAlert : public IAlertStrategy {
public:
  void sendAlert(BreachType breachType) const override {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
  }
};

class EmailAlert : public IAlertStrategy {
public:
  void sendAlert(BreachType breachType) const override {
    const char* recipient = "a.b@c.com";
    switch (breachType) {
      case TOO_LOW:
        printf("To: %s\nHi, the temperature is too low\n", recipient);
        break;
      case TOO_HIGH:
        printf("To: %s\nHi, the temperature is too high\n", recipient);
        break;
      case NORMAL:
        break;
    }
  }
};

// Factory functions to select appropriate strategies
std::unique_ptr<ICoolingStrategy> selectCoolingStrategy(CoolingType coolingType) {
  switch (coolingType) {
    case PASSIVE_COOLING: return std::make_unique<PassiveCooling>();
    case HI_ACTIVE_COOLING: return std::make_unique<HiActiveCooling>();
    case MED_ACTIVE_COOLING: return std::make_unique<MedActiveCooling>();
  }
  return nullptr;
}

std::unique_ptr<IAlertStrategy> selectAlertStrategy(AlertTarget alertTarget) {
  switch (alertTarget) {
    case TO_CONTROLLER: return std::make_unique<ControllerAlert>();
    case TO_EMAIL: return std::make_unique<EmailAlert>();
  }
  return nullptr;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  auto coolingStrategy = selectCoolingStrategy(batteryChar.coolingType);
  auto alertStrategy = selectAlertStrategy(alertTarget);

  if (coolingStrategy && alertStrategy) {
    BreachType breachType = coolingStrategy->classifyTemperature(temperatureInC);
    alertStrategy->sendAlert(breachType);
  }
}
