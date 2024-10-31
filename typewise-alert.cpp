#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) {
    return TOO_LOW;
  }
  if (value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  // Replace with a helper function to get limits
  auto [lowerLimit, upperLimit] = getCoolingLimits(coolingType);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch (alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";
  
  const char* message = getBreachMessage(breachType);
  if (message) {
    printf("To: %s\n", recipient);
    printf("%s\n", message);
  }
}

const char* getBreachMessage(BreachType breachType) {
  if (breachType == TOO_LOW) {
    return "Hi, the temperature is too low";
  } else if (breachType == TOO_HIGH) {
    return "Hi, the temperature is too high";
  }
  return nullptr; // Return nullptr for NORMAL or if there's no breach
}

// Function to get cooling limits based on cooling type
std::pair<int, int> getCoolingLimits(CoolingType coolingType) {
  switch (coolingType) {
    case PASSIVE_COOLING:
      return {0, 35};
    case HI_ACTIVE_COOLING:
      return {0, 45};
    case MED_ACTIVE_COOLING:
      return {0, 40};
  }
  return {0, 0}; // Default case
}


