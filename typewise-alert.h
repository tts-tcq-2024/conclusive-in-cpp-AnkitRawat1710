#pragma once
#include <string>

enum class CoolingType { PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING };
enum class BreachType { NORMAL, TOO_LOW, TOO_HIGH };
enum class AlertTarget { TO_CONTROLLER, TO_EMAIL };

struct BatteryCharacter {
    CoolingType coolingType;
    std::string brand;
};

// Abstract base class for alert mechanism
class AlertHandler {
public:
    virtual void sendAlert(BreachType breachType) = 0;
    virtual ~AlertHandler() = default;
};

// Controller alert implementation
class ControllerAlert : public AlertHandler {
public:
    void sendAlert(BreachType breachType) override;
};

// Email alert implementation
class EmailAlert : public AlertHandler {
public:
    void sendAlert(BreachType breachType) override;
};

// Cooling limit handler class
class CoolingLimitHandler {
public:
    static BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
private:
    static BreachType inferBreach(double value, double lowerLimit, double upperLimit);
};

// Main function to check and alert
void checkAndAlert(AlertHandler* alertHandler, BatteryCharacter batteryChar, double temperatureInC);

