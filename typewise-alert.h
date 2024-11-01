#pragma once
#include <memory>
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

// Interface for Breach Classification Strategy
class IBreachClassifier {
public:
  virtual ~IBreachClassifier() = default;
  virtual BreachType classify(double temperatureInC) const = 0;
};

// Interface for Alert Strategy
class IAlert {
public:
  virtual ~IAlert() = default;
  virtual void send(BreachType breachType) const = 0;
};

// Factory function declarations
std::unique_ptr<IBreachClassifier> createBreachClassifier(CoolingType coolingType);
std::unique_ptr<IAlert> createAlert(AlertTarget alertTarget);

// Core function
void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);

// Utility function
BreachType inferBreach(double value, double lowerLimit, double upperLimit);

