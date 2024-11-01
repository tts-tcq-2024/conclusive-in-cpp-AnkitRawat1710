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

// Abstract base class for Breach Classification Strategy
class IBreachClassifier {
public:
  virtual ~IBreachClassifier() = default;
  virtual BreachType classify(double temperatureInC) const = 0;
};

// Abstract base class for Alert Strategy
class IAlert {
public:
  virtual ~IAlert() = default;
  virtual void send(BreachType breachType) const = 0;
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);
