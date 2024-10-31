#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test cases for inferBreach function
TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    // Normal cases
    EXPECT_EQ(inferBreach(10, 0, 20), NORMAL);
    EXPECT_EQ(inferBreach(15, 0, 20), NORMAL);
    EXPECT_EQ(inferBreach(20, 0, 20), NORMAL);
    
    // Edge cases
    EXPECT_EQ(inferBreach(0, 0, 20), NORMAL); // At lower limit
    EXPECT_EQ(inferBreach(20, 0, 20), NORMAL); // At upper limit
    
    // Too low cases
    EXPECT_EQ(inferBreach(-1, 0, 20), TOO_LOW); // Below lower limit
    EXPECT_EQ(inferBreach(0, 1, 20), TOO_LOW); // At lower limit but exceeds acceptable range

    // Too high cases
    EXPECT_EQ(inferBreach(21, 0, 20), TOO_HIGH); // Above upper limit
    EXPECT_EQ(inferBreach(30, 0, 20), TOO_HIGH); // Well above upper limit
}

// Test cases for classifyTemperatureBreach function
TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    // Passive cooling tests
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 35), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW); // below acceptable

    // High active cooling tests
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL); // at upper limit
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH); // above upper limit

    // Medium active cooling tests
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 35), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40), NORMAL); // at upper limit
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH); // above upper limit
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5), TOO_LOW); // below acceptable
}

// Test cases for checkAndAlert function
TEST(TypeWiseAlertTestSuite, CheckAndAlertFunctionality) {
    BatteryCharacter batteryChar;
    
    // Passive cooling scenarios
    batteryChar.coolingType = PASSIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 30);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("feed"), std::string::npos); // Controller alert output

    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 30);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n"); // Low alert

    // High active cooling scenarios
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 46);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n"); // High alert

    // Medium active cooling scenarios
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 41);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n"); // High alert
}

// Test cases for edge cases in checkAndAlert
TEST(TypeWiseAlertTestSuite, CheckAndAlertEdgeCases) {
    BatteryCharacter batteryChar;

    // Edge cases for passive cooling
    batteryChar.coolingType = PASSIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 0); // At lower limit
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n"); // Should trigger low alert

    // Edge case for upper limit with high active cooling
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 45); // At upper limit
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n"); // Should trigger high alert

    // Ensure normal conditions do not trigger alerts
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 35); // Normal condition
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, ""); // No alert should be triggered
}
