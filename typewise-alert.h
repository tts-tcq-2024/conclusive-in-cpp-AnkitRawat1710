// typewise-alert.h
#pragma once
#include <memory>

enum CoolingType { PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING };
enum BreachType { NORMAL, TOO_LOW, TOO_HIGH };
enum AlertTarget { TO_CONTROLLER, TO_EMAIL };

struct BatteryCharacter {
    CoolingType coolingType;
    char brand[48];
};

class AlertHandler {
public:
    virtual ~AlertHandler() = default;
    virtual void sendAlert(BreachType breachType) const = 0;
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
