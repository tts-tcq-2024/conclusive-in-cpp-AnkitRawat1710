// typewise-alert.tests.cpp
#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
  EXPECT_EQ(inferBreach(30, 20, 40), BreachType::NORMAL);
  EXPECT_EQ(inferBreach(15, 20, 40), BreachType::TOO_LOW);
  EXPECT_EQ(inferBreach(45, 20, 40), BreachType::TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachForCoolingTypes) {
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 20), BreachType::NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 36), BreachType::TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 46), BreachType::TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 41), BreachType::TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
  ControllerAlert controllerAlert;
  testing::internal::CaptureStdout();
  controllerAlert.sendAlert(BreachType::TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("feed : 2"), std::string::npos);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
  EmailAlert emailAlert;
  testing::internal::CaptureStdout();
  emailAlert.sendAlert(BreachType::TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("To: a.b@c.com\nHi, the temperature is too high\n"), std::string::npos);
}
