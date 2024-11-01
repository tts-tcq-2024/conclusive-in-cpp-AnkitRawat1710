// typewise-alert.h
#pragma once
#include <string>

enum class CoolingType { PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING };
enum class BreachType { NORMAL, TOO_LOW, TOO_HIGH };
enum class AlertTarget { TO_CONTROLLER, TO_EMAIL };

struct BatteryCharacter {
  CoolingType coolingType;
  std::string brand;
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);
