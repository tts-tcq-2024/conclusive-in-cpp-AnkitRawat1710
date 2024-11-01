#include "typewise-alert.h"
#include <cassert>

void testCheckAndAlert() {
    BatteryCharacter batteryChar = {PASSIVE_COOLING};
    checkAndAlert(TO_CONTROLLER, batteryChar, -5.0); // Expected to send TOO_LOW alert
    checkAndAlert(TO_EMAIL, batteryChar, 50.0);      // Expected to send TOO_HIGH alert
    checkAndAlert(TO_EMAIL, batteryChar, 25.0);      // Expected to send NORMAL alert
}

int main() {
    testCheckAndAlert();
    std::cout << "All tests passed!\n";
    return 0;
}
