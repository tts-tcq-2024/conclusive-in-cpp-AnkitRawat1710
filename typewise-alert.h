#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <memory>

enum AlertTarget { TO_CONTROLLER, TO_EMAIL };
enum CoolingType { PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING };
enum BreachType { NORMAL, TOO_LOW, TOO_HIGH };

struct BatteryCharacter {
    CoolingType coolingType;
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

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

#endif // TYPEWISE_ALERT_H
