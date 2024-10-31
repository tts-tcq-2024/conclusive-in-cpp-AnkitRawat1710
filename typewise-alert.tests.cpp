#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test inferBreach
TEST(TypeWiseAlertTestSuite, InfersBreachTooLow) {
  ASSERT_EQ(inferBreach(-5, 0, 35), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite, InfersBreachTooHigh) {
  ASSERT_EQ(inferBreach(50, 0, 35), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, InfersBreachNormal) {
  ASSERT_EQ(inferBreach(25, 0, 35), NORMAL);
}

// Test Cooling Strategies
TEST(TypeWiseAlertTestSuite, PassiveCoolingBreach) {
  PassiveCooling cooling;
  ASSERT_EQ(cooling.classifyTemperature(36), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, HiActiveCoolingBreach) {
  HiActiveCooling cooling;
  ASSERT_EQ(cooling.classifyTemperature(46), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, MedActiveCoolingBreach) {
  MedActiveCooling cooling;
  ASSERT_EQ(cooling.classifyTemperature(41), TOO_HIGH);
}

// Test Alerts (mocked by output verification in actual test runs)
TEST(TypeWiseAlertTestSuite, ControllerAlertTest) {
  ControllerAlert alert;
  testing::internal::CaptureStdout();
  alert.sendAlert(TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, EmailAlertTooLowTest) {
  EmailAlert alert;
  testing::internal::CaptureStdout();
  alert.sendAlert(TOO_LOW);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");
}

TEST(TypeWiseAlertTestSuite, EmailAlertTooHighTest) {
  EmailAlert alert;
  testing::internal::CaptureStdout();
  alert.sendAlert(TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

// End-to-End Test for checkAndAlert
TEST(TypeWiseAlertTestSuite, CheckAndAlertToController) {
  BatteryCharacter battery{HI_ACTIVE_COOLING, "TestBrand"};
  testing::internal::CaptureStdout();
  checkAndAlert(TO_CONTROLLER, battery, 46);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmail) {
  BatteryCharacter battery{MED_ACTIVE_COOLING, "TestBrand"};
  testing::internal::CaptureStdout();
  checkAndAlert(TO_EMAIL, battery, 41);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}
