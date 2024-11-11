### Test 1

|Title|Details|
|--|--|
|Function Name|`test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan`|
|Description|This test validates the functionality of updating bridge information and checks if a VLAN exists in the bridge.|
|Test Group|Module: 02|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Enter the test function for updating bridge info and checking if a VLAN exists in the bridge | Not applicable | Not applicable | Should be successful |
| 02 | Log the entry into the test function | Not applicable | Not applicable | Should be successful |
| 03 | Initialize a result variable for evaluating the test outcome | result = 0 | Not applicable | Should be successful |
| 04 | Create a character array for storing the interface name to be updated | ifNameToBeUpdated = {"\0"} | Not applicable | Should be successful |


### Test 2

|Title|Details|
|--|--|
|Function Name|`test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi`|
|Description|This test validates updating of bridge info and checks if a wifi interface exists in bridge utilising the hal API|
|Test Group|Module : 02|
|Test Case ID|002|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :** 
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Entry into the test function and initialisation| ifNameToBeUpdated = "\0", result = 0 | N/A | Should be successful |
| 02 | Invoke the API for updating the bridge info and check if the interface is listed under wifi  | Interface name to be updated = "\0", Result is an integer variable initialized to 0 | Result of the success of the function, can be 0 or 1 | Should be successful |   


### Test 3

|Title|Details|
|--|--|
|Function Name|`test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca`|
|Description|This test validates the functionality of the function updateBridgeInfo_checkIfExistsInBridge_moca in l2 bridge utility HAL. Particularly, it checks if a specific network interface exists in the bridge or not.|
|Test Group|Module : 02|
|Test Case ID|003|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Test begins, log entry is created with entering message | log message = "Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca..." | Success log entry | Should be successful |
| 02 | The variable 'result' is initialized with a value of 0 | result = 0 | Value of 'result' should be 0 | Should be successful |
| 03 | The character array 'ifNameToBeUpdated' is initialized with a null value | ifNameToBeUpdated[64] =  {"\0"} | The 'ifNameToBeUpdated' should initialize with no value (empty string) | Should be successful |

### Test 4

|Title|Details|
|--|--|
|Function Name|`test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre`|
|Description|Test the functionality of the L2 Bridge utility API to update Bridge Information and check if a particular interface exists in the bridge using the GRE tunnel.|
|Test Group|Module : 02|
|Test Case ID|004|
|Priority|High|

**Pre-Conditions:**
None

**Dependencies:**
None

**User Interaction:**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Logging the start of the test. No input to the function under test. | N/A | N/A | Should be successful |
| 02 | Initialize variable 'result' to keep track of success or failure of steps and char array 'ifNameToBeUpdated' which is expected to contain the interface name to be updated. | result = 0, ifNameToBeUpdated = {"\0"} | N/A | Should be successful |

### Test 5

|Title|Details|
|--|--|
|Function Name|`test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth`|
|Description|Test the functionality of updating bridge info and checking if the given name exists in the bridge ethernet.|
|Test Group|Module : 02|
|Test Case ID|005|
|Priority|High|

**Pre-Conditions:**
None

**Dependencies:** None

**User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Log the starting of the test | Not applicable | Log entry added | Should be successful |
| 02 | Initialize variables and set up the testing environment | result = 0, ifNameToBeUpdated= "\0" | Variables initialized | Should be successful |