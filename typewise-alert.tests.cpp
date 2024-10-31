#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test for inferring breaches
TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(0, 1, 10), TOO_LOW);
    EXPECT_EQ(inferBreach(5, 1, 10), NORMAL);
    EXPECT_EQ(inferBreach(15, 1, 10), TOO_HIGH);
}

// Test for classifying temperature breaches
TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40), TOO_HIGH);

    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50), TOO_HIGH);

    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45), TOO_HIGH);
}

// Test for check and alert functionality (mocking stdout)
TEST(TypeWiseAlertTestSuite, CheckAndAlertFunctionality) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "Battery A"};
    testing::internal::CaptureStdout(); // Start capturing stdout

    checkAndAlert(TO_EMAIL, batteryChar, -1); // Expect "too low" alert
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos);

    checkAndAlert(TO_EMAIL, batteryChar, 36); // Expect "too high" alert
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos);

    checkAndAlert(TO_EMAIL, batteryChar, 30); // Expect no alert
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Hi, the temperature is too low"), std::string::npos);
}

// Edge case tests
TEST(TypeWiseAlertTestSuite, CheckAndAlertEdgeCases) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "Battery B"};
    testing::internal::CaptureStdout(); // Start capturing stdout

    checkAndAlert(TO_EMAIL, batteryChar, -1); // Expect "too low" alert
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos);

    checkAndAlert(TO_EMAIL, batteryChar, 46); // Expect "too high" alert
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos);

    checkAndAlert(TO_EMAIL, batteryChar, 0); // Expect no alert
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Hi, the temperature is too low"), std::string::npos);
}


