#pragma once

#include <string>

enum class CoolingType {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
};

enum class BreachType {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
};

enum class AlertTarget {
  TO_CONTROLLER,
  TO_EMAIL
};

struct BatteryCharacter {
  CoolingType coolingType;
  std::string brand;
};

class AlertHandler {
public:
  virtual void sendAlert(BreachType breachType) const = 0;
  virtual ~AlertHandler() = default;
};

class ControllerAlertHandler : public AlertHandler {
public:
  void sendAlert(BreachType breachType) const override;
};

class EmailAlertHandler : public AlertHandler {
public:
  void sendAlert(BreachType breachType) const override;
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
