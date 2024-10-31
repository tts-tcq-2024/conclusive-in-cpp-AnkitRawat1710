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

// Helper function to check output messages for sending alerts
void checkEmailOutput(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, const std::string& expectedMessage) {
    testing::internal::CaptureStdout(); // Start capturing stdout
    checkAndAlert(alertTarget, batteryChar, temperatureInC); // Trigger alert
    std::string output = testing::internal::GetCapturedStdout(); // Get captured output
    EXPECT_NE(output.find(expectedMessage), std::string::npos); // Check for expected message
}

// Test for check and alert functionality
TEST(TypeWiseAlertTestSuite, CheckAndAlertFunctionality) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "Battery A"};
    
    checkEmailOutput(TO_EMAIL, batteryChar, -1, "Hi, the temperature is too low"); // Expect "too low" alert
    checkEmailOutput(TO_EMAIL, batteryChar, 36, "Hi, the temperature is too high"); // Expect "too high" alert
    checkEmailOutput(TO_EMAIL, batteryChar, 30, ""); // Expect no alert
}

// Edge case tests
TEST(TypeWiseAlertTestSuite, CheckAndAlertEdgeCases) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "Battery B"};
    
    checkEmailOutput(TO_EMAIL, batteryChar, -1, "Hi, the temperature is too low"); // Expect "too low" alert
    checkEmailOutput(TO_EMAIL, batteryChar, 46, "Hi, the temperature is too high"); // Expect "too high" alert
    checkEmailOutput(TO_EMAIL, batteryChar, 0, ""); // Expect no alert
}




