#pragma once

#include <string>

enum CoolingType {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
};

enum BreachType {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
};

enum AlertTarget {
  TO_CONTROLLER,
  TO_EMAIL
};

struct BatteryCharacter {
  CoolingType coolingType;
  std::string brand;
};

class ICoolingStrategy {
public:
  virtual ~ICoolingStrategy() = default;
  virtual BreachType classifyTemperature(double temperature) const = 0;
};

class IAlertStrategy {
public:
  virtual ~IAlertStrategy() = default;
  virtual void sendAlert(BreachType breachType) const = 0;
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
