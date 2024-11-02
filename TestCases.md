
| **Test Case ID** | **Test Description** | **Inputs** | **Expected Output** | **Rationale** |
|------------------|----------------------|------------|---------------------|---------------|
| TC01 | Test `inferBreach` with value below limit | Value = -5, Limits = (0, 35) | TOO_LOW | To confirm `inferBreach` correctly identifies temperatures lower than the allowable range as TOO_LOW. |
| TC02 | Test `inferBreach` with value above limit | Value = 40, Limits = (0, 35) | TOO_HIGH | To ensure `inferBreach` properly flags values exceeding the upper limit as TOO_HIGH. |
| TC03 | Test `inferBreach` with normal value | Value = 20, Limits = (0, 35) | NORMAL | To verify `inferBreach` can recognize temperatures within acceptable limits as NORMAL. |
| TC04 | Test `inferBreach` at lower boundary | Value = 0, Limits = (0, 35) | NORMAL | Edge case test to confirm `inferBreach` handles the lower boundary condition and returns NORMAL. |
| TC05 | Test `inferBreach` at upper boundary | Value = 35, Limits = (0, 35) | NORMAL | Edge case test to confirm `inferBreach` handles the upper boundary and returns NORMAL. |
| TC06 | Test Passive Cooling for TOO_LOW | CoolingType = PASSIVE_COOLING, Temperature = -1 | TOO_LOW alert to controller | To validate that `checkAndAlert` sends a TOO_LOW alert to the controller when temperature is below limit for Passive Cooling. |
| TC07 | Test Passive Cooling for TOO_HIGH | CoolingType = PASSIVE_COOLING, Temperature = 36 | TOO_HIGH alert to controller | To verify that a TOO_HIGH alert is sent to the controller when temperature exceeds the limit for Passive Cooling. |
| TC08 | Test Passive Cooling for NORMAL | CoolingType = PASSIVE_COOLING, Temperature = 20 | NORMAL alert to controller | To ensure that NORMAL is correctly recognized and sent as a status update to the controller for Passive Cooling. |
| TC09 | Test Passive Cooling at Lower Boundary | CoolingType = PASSIVE_COOLING, Temperature = 0 | NORMAL alert to controller | Edge case to confirm proper handling of the lower limit in Passive Cooling as NORMAL. |
| TC10 | Test Passive Cooling at Upper Boundary | CoolingType = PASSIVE_COOLING, Temperature = 35 | NORMAL alert to controller | Edge case to confirm proper handling of the upper limit in Passive Cooling as NORMAL. |
| TC11 | Test High Active Cooling for TOO_LOW | CoolingType = HI_ACTIVE_COOLING, Temperature = -1 | TOO_LOW email alert | To validate that `checkAndAlert` sends a TOO_LOW email alert when temperature falls below acceptable range for High Active Cooling. |
| TC12 | Test High Active Cooling for TOO_HIGH | CoolingType = HI_ACTIVE_COOLING, Temperature = 46 | TOO_HIGH email alert | To verify `checkAndAlert` sends a TOO_HIGH email alert when temperature exceeds the range for High Active Cooling. |
| TC13 | Test High Active Cooling for NORMAL | CoolingType = HI_ACTIVE_COOLING, Temperature = 20 | NORMAL email alert | To ensure NORMAL condition is correctly processed and emailed for High Active Cooling. |
| TC14 | Test High Active Cooling at Lower Boundary | CoolingType = HI_ACTIVE_COOLING, Temperature = 0 | NORMAL email alert | Edge case to confirm the lower limit is managed as NORMAL in High Active Cooling. |
| TC15 | Test High Active Cooling at Upper Boundary | CoolingType = HI_ACTIVE_COOLING, Temperature = 45 | NORMAL email alert | Edge case to confirm the upper limit is managed as NORMAL in High Active Cooling. |
| TC16 | Test Medium Active Cooling for TOO_LOW | CoolingType = MED_ACTIVE_COOLING, Temperature = -1 | TOO_LOW email alert | To validate that `checkAndAlert` sends a TOO_LOW email alert for temperature below range in Medium Active Cooling. |
| TC17 | Test Medium Active Cooling for TOO_HIGH | CoolingType = MED_ACTIVE_COOLING, Temperature = 41 | TOO_HIGH email alert | To confirm that a TOO_HIGH email alert is sent when the temperature exceeds range for Medium Active Cooling. |
| TC18 | Test Medium Active Cooling for NORMAL | CoolingType = MED_ACTIVE_COOLING, Temperature = 20 | NORMAL email alert | To ensure that the NORMAL status is correctly processed and emailed for Medium Active Cooling. |
| TC19 | Test Medium Active Cooling at Lower Boundary | CoolingType = MED_ACTIVE_COOLING, Temperature = 0 | NORMAL email alert | Edge case to verify the lower boundary in Medium Active Cooling is correctly classified as NORMAL. |
| TC20 | Test Medium Active Cooling at Upper Boundary | CoolingType = MED_ACTIVE_COOLING, Temperature = 40 | NORMAL email alert | Edge case to confirm the upper boundary in Medium Active Cooling is correctly classified as NORMAL. |
| TC21 | Test Controller Alert with TOO_LOW | AlertTarget = TO_CONTROLLER, BreachType = TOO_LOW | TOO_LOW alert to controller | To verify the controller alert system correctly handles a TOO_LOW alert. |
| TC22 | Test Controller Alert with TOO_HIGH | AlertTarget = TO_CONTROLLER, BreachType = TOO_HIGH | TOO_HIGH alert to controller | To confirm that a TOO_HIGH breach is properly sent to the controller. |
| TC23 | Test Controller Alert with NORMAL | AlertTarget = TO_CONTROLLER, BreachType = NORMAL | NORMAL alert to controller | To validate that NORMAL status is properly handled by the controller alert system. |
| TC24 | Test Email Alert with TOO_LOW | AlertTarget = TO_EMAIL, BreachType = TOO_LOW | TOO_LOW email alert with message | To confirm that the email alert system sends a TOO_LOW alert with the appropriate message. |
| TC25 | Test Email Alert with TOO_HIGH | AlertTarget = TO_EMAIL, BreachType = TOO_HIGH | TOO_HIGH email alert with message | To verify the email alert system sends a TOO_HIGH alert with the correct message. |
| TC26 | Test Email Alert with NORMAL | AlertTarget = TO_EMAIL, BreachType = NORMAL | No email alert sent | To ensure that no email is sent for NORMAL breaches. |
| TC27 | Test Invalid CoolingType for Breach Classifier Factory | Invalid CoolingType (-1) | Throws std::invalid_argument exception | To confirm the breach classifier factory correctly throws an exception on an invalid CoolingType. |
| TC28 | Test Invalid AlertTarget for Alert Factory | Invalid AlertTarget (-1) | Throws std::invalid_argument exception | To verify the alert factory throws an exception on invalid AlertTarget input. |

