#include <gtest/gtest.h>
#include "typewise-alert.h"

// Helper functions to streamline test cases
BatteryCharacter createBatteryCharacter(CoolingType coolingType, const std::string& brand) {
  return BatteryCharacter{coolingType, brand};
}

TEST(TypeWiseAlertTestSuite, InferBreachAccordingToLimits) {
  EXPECT_EQ(inferBreach(-1, 0, 35), BreachType::TOO_LOW);
  EXPECT_EQ(inferBreach(36, 0, 35), BreachType::TOO_HIGH);
  EXPECT_EQ(inferBreach(20, 0, 35), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, PassiveCoolingBreachClassification) {
  BatteryCharacter battery = createBatteryCharacter(CoolingType::PASSIVE_COOLING, "BrandA");
  checkAndAlert(AlertTarget::TO_CONTROLLER, battery, 36); // Expect to go to controller as TOO_HIGH
}

TEST(TypeWiseAlertTestSuite, HiActiveCoolingBreachClassification) {
  BatteryCharacter battery = createBatteryCharacter(CoolingType::HI_ACTIVE_COOLING, "BrandB");
  checkAndAlert(AlertTarget::TO_EMAIL, battery, 46); // Expect email alert as TOO_HIGH
}

TEST(TypeWiseAlertTestSuite, MedActiveCoolingBreachClassification) {
  BatteryCharacter battery = createBatteryCharacter(CoolingType::MED_ACTIVE_COOLING, "BrandC");
  checkAndAlert(AlertTarget::TO_EMAIL, battery, 39); // Expect email alert as NORMAL
}
