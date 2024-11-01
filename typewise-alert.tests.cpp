#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
  EXPECT_EQ(inferBreach(-5, 0, 35), BreachType::TOO_LOW);
  EXPECT_EQ(inferBreach(50, 0, 45), BreachType::TOO_HIGH);
  EXPECT_EQ(inferBreach(30, 0, 40), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 36), BreachType::TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 46), BreachType::TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 39), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, SendsControllerAlert) {
  ControllerAlertHandler controllerAlert;
  testing::internal::CaptureStdout();
  controllerAlert.sendAlert(BreachType::TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());
}

TEST(TypeWiseAlertTestSuite, SendsEmailAlert) {
  EmailAlertHandler emailAlert;
  testing::internal::CaptureStdout();
  emailAlert.sendAlert(BreachType::TOO_LOW);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());
}

