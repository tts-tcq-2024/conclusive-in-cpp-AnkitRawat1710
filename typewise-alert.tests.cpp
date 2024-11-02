#include <gtest/gtest.h>
#include "typewise-alert.h"
#include <stdexcept>

// Helper function to create BatteryCharacter instances
BatteryCharacter createBatteryCharacter(CoolingType coolingType, const std::string& brand) {
    return BatteryCharacter{coolingType, brand};
}

// Infer Breach Functionality Tests
TEST(TypeWiseAlertTestSuite, InferBreachLevels) {
    EXPECT_EQ(inferBreach(-5, 0, 35), BreachType::TOO_LOW);
    EXPECT_EQ(inferBreach(40, 0, 35), BreachType::TOO_HIGH);
    EXPECT_EQ(inferBreach(20, 0, 35), BreachType::NORMAL);
    EXPECT_EQ(inferBreach(0, 0, 35), BreachType::NORMAL);    // Boundary: Lower limit
    EXPECT_EQ(inferBreach(35, 0, 35), BreachType::NORMAL);   // Boundary: Upper limit
}

// Passive Cooling Breach Classification Tests
TEST(TypeWiseAlertTestSuite, PassiveCoolingBreachLevels) {
    BatteryCharacter battery = createBatteryCharacter(CoolingType::PASSIVE_COOLING, "BrandA");
    checkAndAlert(TO_CONTROLLER, battery, -1);   // TOO_LOW alert
    checkAndAlert(TO_CONTROLLER, battery, 36);   // TOO_HIGH alert
    checkAndAlert(TO_CONTROLLER, battery, 20);   // NORMAL alert
    checkAndAlert(TO_CONTROLLER, battery, 0);    // Boundary: Lower limit NORMAL
    checkAndAlert(TO_CONTROLLER, battery, 35);   // Boundary: Upper limit NORMAL
}

// High Active Cooling Breach Classification Tests
TEST(TypeWiseAlertTestSuite, HiActiveCoolingBreachLevels) {
    BatteryCharacter battery = createBatteryCharacter(CoolingType::HI_ACTIVE_COOLING, "BrandB");
    checkAndAlert(TO_EMAIL, battery, -1);        // TOO_LOW email alert
    checkAndAlert(TO_EMAIL, battery, 46);        // TOO_HIGH email alert
    checkAndAlert(TO_EMAIL, battery, 20);        // NORMAL email alert
    checkAndAlert(TO_EMAIL, battery, 0);         // Boundary: Lower limit NORMAL
    checkAndAlert(TO_EMAIL, battery, 45);        // Boundary: Upper limit NORMAL
}

// Medium Active Cooling Breach Classification Tests
TEST(TypeWiseAlertTestSuite, MedActiveCoolingBreachLevels) {
    BatteryCharacter battery = createBatteryCharacter(CoolingType::MED_ACTIVE_COOLING, "BrandC");
    checkAndAlert(TO_EMAIL, battery, -1);        // TOO_LOW email alert
    checkAndAlert(TO_EMAIL, battery, 41);        // TOO_HIGH email alert
    checkAndAlert(TO_EMAIL, battery, 20);        // NORMAL email alert
    checkAndAlert(TO_EMAIL, battery, 0);         // Boundary: Lower limit NORMAL
    checkAndAlert(TO_EMAIL, battery, 40);        // Boundary: Upper limit NORMAL
}

// Alert Mechanism Tests for Breach Types
TEST(TypeWiseAlertTestSuite, AlertMechanismBreachTypes) {
    ControllerAlert controllerAlert;
    controllerAlert.send(BreachType::TOO_LOW);    // TOO_LOW to controller
    controllerAlert.send(BreachType::TOO_HIGH);   // TOO_HIGH to controller
    controllerAlert.send(BreachType::NORMAL);     // NORMAL to controller

    EmailAlert emailAlert;
    emailAlert.send(BreachType::TOO_LOW);         // TOO_LOW email alert
    emailAlert.send(BreachType::TOO_HIGH);        // TOO_HIGH email alert
    emailAlert.send(BreachType::NORMAL);          // NORMAL email alert (should not send)
}

// Invalid Input Tests for Factory Functions
TEST(TypeWiseAlertTestSuite, InvalidInputs) {
    EXPECT_THROW(createBreachClassifier(static_cast<CoolingType>(-1)), std::invalid_argument);
    EXPECT_THROW(createAlert(static_cast<AlertTarget>(-1)), std::invalid_argument);
}
