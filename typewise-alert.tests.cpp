#include <gtest/gtest.h>
#include "typewise-alert.h"
#include <sstream>
#include <string>

// Function to capture console output
std::string captureOutput(void (*func)(AlertTarget, BatteryCharacter, double), AlertTarget target, BatteryCharacter batteryChar, double temperature) {
    // Redirect cout to a string stream
    std::ostringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    func(target, batteryChar, temperature);  // Call the function

    std::cout.rdbuf(oldCoutBuffer);  // Restore cout
    return buffer.str();  // Return captured output
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 34), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 0), NORMAL); // Edge case: exactly at lower limit
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL); // Edge case: exactly at upper limit
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertFunctionality) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandA"};
    
    // Test sending TOO_HIGH alert
    std::string output = captureOutput(checkAndAlert, TO_EMAIL, batteryChar, 36);
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos); // Check if the alert was sent

    // Test sending NORMAL alert
    output = captureOutput(checkAndAlert, TO_EMAIL, batteryChar, 34);
    EXPECT_EQ(output, ""); // No alert should be sent for NORMAL
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertEdgeCases) {
    BatteryCharacter batteryCharHiActive = {HI_ACTIVE_COOLING, "BrandB"};
    
    // Test sending NORMAL alert at upper limit
    std::string output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharHiActive, 45);
    EXPECT_EQ(output, ""); // No alert for NORMAL
    
    // Test sending TOO_HIGH alert
    output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharHiActive, 46);
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos); // Alert sent for TOO_HIGH

    // Test sending TOO_LOW alert
    output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharHiActive, -1);
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos); // Alert sent for TOO_LOW
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertMedActiveCooling) {
    BatteryCharacter batteryCharMedActive = {MED_ACTIVE_COOLING, "BrandC"};

    // Test sending NORMAL alert at upper limit
    std::string output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharMedActive, 40);
    EXPECT_EQ(output, ""); // No alert for NORMAL

    // Test sending TOO_HIGH alert
    output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharMedActive, 41);
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos); // Alert sent for TOO_HIGH

    // Test sending TOO_LOW alert
    output = captureOutput(checkAndAlert, TO_EMAIL, batteryCharMedActive, -1);
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos); // Alert sent for TOO_LOW
}

