/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:*
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file test_l1_bridge_util_hal.c
 * @page bridge_util_hal Level 1 Tests
 *
 * ## Module's Role
 * This module includes Level 1 functional tests (success and failure scenarios).
 * This is to ensure that the bridge_util_hal APIs meet the requirements across all vendors.
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
 */

#include <ut.h>
#include <ut_log.h>
#include "bridge_util_hal.h"
#include "network_interface.h"
#include <ut_kvp_profile.h>

static int gTestGroup = 1;
static int gTestID = 1;

char ifName[64];
char br_Name[64];
char iface_to_remove[64];
char ifNameToBeUpdated[64];
int InstanceNumber;

bridgeDetails br_details;

/**function to read the kvp profile file and return its content as a string
 *IN : kvp profile path
 *OUT : content of profile file
 **/

int fetch_bridge_util_details(void)
{
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/br_Name", br_Name);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/ifaceName", ifName);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/ifNameToBeUpdated", ifNameToBeUpdated);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/iface_to_remove", iface_to_remove);

    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/bridgeName", br_details.bridgeName);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/vlan_name", br_details.vlan_name);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/VirtualParentIfname", br_details.VirtualParentIfname);
    br_details.vlanID = UT_KVP_PROFILE_GET_UINT32("bridge_util/config/bridgeDetails/vlanID");
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/ethIfList", br_details.ethIfList);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/MoCAIfList", br_details.MoCAIfList);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/GreIfList", br_details.GreIfList);
    UT_KVP_PROFILE_GET_STRING("bridge_util/config/bridgeDetails/WiFiIfList", br_details.WiFiIfList);

    InstanceNumber = UT_KVP_PROFILE_GET_UINT32("bridge_util/config/InstanceNumber");

    return 0;
}
/**
 * @brief Unit test for the updateBridgeInfo function in the l1_bridge_util_hal_positive1 module.
 *
 * This test case verifies the functionality of the updateBridgeInfo function by invoking it with valid parameters and validating the return value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 001 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke updateBridgeInfo with valid BR_CMD and type | bridgeInfo = valid structure, ifNameToBeUpdated = valid buffer, Opr = valid opr enum, type = valid type enum | 0 | Should be successful |
 */
void test_l1_bridge_util_hal_positive1_updateBridgeInfo(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    BR_CMD Opr = IF_DOWN_CMD;
    IF_TYPE type = BRIDGE_IF_TYPE;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);
        UT_LOG_DEBUG("Interface name To be Updated : %s", ifNameToBeUpdated);

        UT_LOG_DEBUG("Invoking updateBridgeInfo with valid Opr : %d , type : %d", Opr, type);
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result);
        UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
        UT_ASSERT_EQUAL(result, 0);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test for the updateBridgeInfo function with positive test cases.
 *
 * This test case verifies the functionality of the updateBridgeInfo function by testing it with different values of Opr parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 002 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoke updateBridgeInfo with Opr = 1 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = 1, type = valid buffer | 0 | Should be successful |
 * | 02 | Invoke updateBridgeInfo with Opr = 2 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = 2, type = valid buffer | 0 | Should be successful |
 * | 03 | Invoke updateBridgeInfo with Opr = 3 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = 3, type = valid buffer | 0 | Should be successful |
 * | 04 | Invoke updateBridgeInfo with Opr = 4 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = 4, type = valid buffer | 0 | Should be successful |
 */
void test_l1_bridge_util_hal_positive2_updateBridgeInfo(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    int Opr = 1;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    int type = IF_BRIDGE_BRIDGEUTIL;

    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);
        UT_LOG_DEBUG("Interface name To be Updated : %s", ifNameToBeUpdated);

        for (Opr = 1; Opr <= 4; Opr++)
        {
            UT_LOG_DEBUG("Invoking updateBridgeInfo with valid Opr = %d", Opr);
            result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
            UT_LOG_DEBUG("updateBridgeInfo returns : %d", result);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
            UT_ASSERT_EQUAL(result, 0);
        }
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This function tests the updateBridgeInfo API with different type values.
 *
 * The objective of this test is to verify the behavior of the updateBridgeInfo API when different type values are passed as input. The updateBridgeInfo API is responsible for updating the bridge details with the specified interface name and operation type. This test ensures that the API returns the expected result for each type value.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 003 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke the updateBridgeInfo API with type = 1 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr =valid buffer, type = 1  | 0 | Should be successful |
 * | 02 | Invoke the updateBridgeInfo API with type = 2 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 2  | 0 | Should be successful |
 * | 03 | Invoke the updateBridgeInfo API with type = 3 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 3 | 0 | Should be successful |
 * | 04 | Invoke the updateBridgeInfo API with type = 4 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 4 | 0 | Should be successful |
 * | 05 | Invoke the updateBridgeInfo API with type = 5 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 5 | 0 | Should be successful |
 * | 06 | Invoke the updateBridgeInfo API with type = 6 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 6 | 0 | Should be successful |
 * | 07 | Invoke the updateBridgeInfo API with type = 7 | bridgeInfo = valid structure , ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = 7 | 0 | Should be successful |
 */
void test_l1_bridge_util_hal_positive3_updateBridgeInfo(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    int Opr = 1;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    int type = 1;

    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);
        UT_LOG_DEBUG("Interface name To be Updated : %s", ifNameToBeUpdated);

        for (type = 1; type <= 7; type++)
        {
            UT_LOG_DEBUG("Invoking updateBridgeInfo with valid type = %d", type);
            result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
            UT_LOG_DEBUG("updateBridgeInfo returns : %d", result);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
            UT_ASSERT_EQUAL(result, 0);
        }
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case for testing the updateBridgeInfo function with NULL ifNameToBeUpdated.
 *
 * This test case is used to verify the behavior of the updateBridgeInfo function when NULL is passed as the ifNameToBeUpdated argument. The updateBridgeInfo function is responsible for updating the bridge information based on the provided input parameters.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 004 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke the API with NULL bridgeInfo | bridgeInfo = NULL structure, ifNameToBeUpdated = valid buffer , Opr = valid buffer, type = valid buffer |  -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative1_updateBridgeInfo(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = NULL;

    BR_CMD Opr = IF_DOWN_CMD;
    IF_TYPE type = BRIDGE_IF_TYPE;

    UT_LOG_DEBUG("Invoking updateBridgeInfo with NULL bridgeInfo.");
    result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
    UT_LOG_DEBUG("updateBridgeInfo returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case for testing the updateBridgeInfo function with NULL ifNameToBeUpdated.
 *
 * This test case is used to verify the behavior of the updateBridgeInfo function when NULL is passed as the ifNameToBeUpdated argument. The updateBridgeInfo function is responsible for updating the bridge information based on the provided input parameters.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 005 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke the API with NULL ifNameToBeUpdated | bridgeInfo = valid buffer, ifNameToBeUpdated = NULL, Opr = valid buffer, type = valid buffer |  -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative2_updateBridgeInfo(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails)); /*TODO : bridgeInfo is a vendor specific value*/

    char *ifName_ToBeUpdated = NULL;

    BR_CMD Opr = IF_DOWN_CMD;
    IF_TYPE type = BRIDGE_IF_TYPE;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking updateBridgeInfo with NULL ifNameToBeUpdated.");
        result = updateBridgeInfo(bridgeInfo, ifName_ToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test case checks the behavior of the updateBridgeInfo function when provided with an invalid Opr value.
 *
 * The test case aims to verify that the updateBridgeInfo function correctly handles the invalid Opr value by returning -1.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 006 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the API with invalid Opr | bridgeInfo = valid structure, ifNameToBeUpdated = valid buffer, invalid Opr, type = valid buffer | -1 | The API should return error |
 */
void test_l1_bridge_util_hal_negative3_updateBridgeInfo(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result1 = 0;
    int result2 = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));

    int Opr = -1;

    IF_TYPE type = BRIDGE_IF_TYPE;

    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking updateBridgeInfo with invalid minimum Opr : %d ", Opr);
        result1 = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result1);

        Opr = 5;
        UT_LOG_DEBUG("Invoking updateBridgeInfo with invalid maximum Opr : %d ", Opr);
        result2 = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result2);

        UT_ASSERT_EQUAL(result1, -1);
        UT_ASSERT_EQUAL(result2, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test to verify the updateBridgeInfo function handles invalid type correctly.
 *
 * The updateBridgeInfo function is tested to ensure that it handles the case where an invalid type is provided as an argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 007 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the updateBridgeInfo API with invalid type | bridgeInfo = valid structure, ifNameToBeUpdated = valid buffer, Opr = valid buffer, invalid type | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative4_updateBridgeInfo(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result1 = 0;
    int result2 = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));

    BR_CMD Opr = IF_DOWN_CMD;
    int type = 0;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Invoking updateBridgeInfo with invalid  min type : %d", type);
        result1 = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result1);

        type = 8;
        UT_LOG_DEBUG("Invoking updateBridgeInfo with invalid maximum type : %d", type);
        result2 = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG_DEBUG("updateBridgeInfo returns : %d", result2);

        UT_ASSERT_EQUAL(result1, -1);
        UT_ASSERT_EQUAL(result2, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Check if the interface exists in the bridge utility
 *
 * This test verifies the functionality of the checkIfExists function in the L1 Bridge Utility module. It checks if the function returns 0 when the interface name is valid.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 008 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke checkIfExists with valid interface | valid interface buffer | 0 | Should return Success |
 */
void test_l1_bridge_util_hal_positive1_checkIfExists(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64] = {"\0"};

    strcpy(iface_name, ifName);

    UT_LOG_DEBUG("Invoking checkIfExists with valid_interface : %s", iface_name);
    result = checkIfExists(iface_name);
    UT_LOG_DEBUG("checkIfExists returns : %d", result);
    UT_ASSERT_EQUAL(result, 0);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test function checks the functionality of the checkIfExists API when a NULL value is passed for the interface name.
 *
 * This test verifies that the checkIfExists API returns -1 when a NULL value is passed for the interface name.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 009 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoking checkIfExists with NULL interface name | NULL interface name | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative1_checkIfExists(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char *iface_name = NULL;

    UT_LOG_DEBUG("Invoking checkIfExists with NULL interface name");
    result = checkIfExists(iface_name);
    UT_LOG_DEBUG("checkIfExists returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Unit test for the checkIfExists function with empty iface_name.
 *
 * This test verifies the behavior of the checkIfExists function when an empty iface_name is passed as input.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 010 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke checkIfExists with empty interface name | empty interface name | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative2_checkIfExists(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64] = "";

    UT_LOG_DEBUG("Invoking checkIfExists with empty interface name");
    result = checkIfExists(iface_name);
    UT_LOG_DEBUG("checkIfExists returns :  %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test the checkIfExists function with an invalid interface name
 *
 * This test verifies that the checkIfExists function returns -1 when passed an invalid interface name.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 011 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke checkIfExists with invalid interface name | invalid interface name | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative3_checkIfExists(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64] = "invalid_interface";

    UT_LOG_DEBUG("Invoking checkIfExists with invalid_interface");
    result = checkIfExists(iface_name);
    UT_LOG_DEBUG("checkIfExists returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test function checks the behavior of the checkIfExistsInBridge function when a valid interface exists in a bridge.
 *
 * The objective of this test is to ensure that the checkIfExistsInBridge function correctly identifies if a given interface exists in a bridge and returns the bridge name if it does.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 012 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
 *
 * **Test Procedure:**  @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke checkIfExistsInBridge with valid interface name | valid interface name , valid Bridge name buffer | 0 | Should return Success |
 */
void test_l1_bridge_util_hal_positive1_checkIfExistsInBridge(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64];
    char bridge_name[64];

    strcpy(iface_name, ifName);
    strcpy(bridge_name, br_Name);

    UT_LOG_DEBUG("Invoking checkIfExistsInBridge with valid interface name: %s and bridge name : %s", iface_name, bridge_name);
    result = checkIfExistsInBridge(iface_name, bridge_name);
    UT_LOG_DEBUG("checkIfExistsInBridge returns : %d", result);
    UT_ASSERT_EQUAL(result, 0);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test the function checkIfExistsInBridge when a valid interface is not present in the bridge.
 *
 * This test is to verify the behavior of the checkIfExistsInBridge function when a valid interface is not present in the bridge. The function should return -1 .
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 013 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke checkIfExistsInBridge with valid interface and the interface is not attached to any bridge | valid interface name, valid bridge name buffer | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative1_checkIfExistsInBridge(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64];

    strcpy(iface_name, ifName);

    char bridge_name[64] = "ert34";

    UT_LOG_DEBUG("Invoking checkIfExistsInBridge with  valid interface:%s not in bridge : %s", iface_name, bridge_name);
    result = checkIfExistsInBridge(iface_name, bridge_name);
    UT_LOG_DEBUG("bridge_name: %s", bridge_name);
    UT_LOG_DEBUG("checkIfExistsInBridge returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test scenario to check if the function returns the correct result when the input interface name is NULL.
 *
 * This test checks if the checkIfExistsInBridge API handles the case where the interface name is NULL
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 014 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke checkIfExistsInBridge with NULL interface | NULL interface name | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative2_checkIfExistsInBridge(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char *iface_name = NULL;
    char bridge_name[64] = {"\0"};

    strcpy(bridge_name, br_Name);

    UT_LOG_DEBUG("Invoking checkIfExistsInBridge with NULL Interface and valid bridge : %s", bridge_name);
    result = checkIfExistsInBridge(iface_name, bridge_name);
    UT_LOG_DEBUG(" bridge_name: %s", bridge_name);
    UT_LOG_DEBUG("checkIfExistsInBridge returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test the function checkIfExistsInBridge() when the bridge name is NULL.
 *
 * This test case verifies the behavior of the checkIfExistsInBridge() function when the bridge name parameter is NULL. The objective is to ensure that the function returns -1 as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 015 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoke checkIfExistsInBridge with valid interface and NULL bridge Name | valid Interface , NULL bridge name | -1 | The function should return error |
 */
void test_l1_bridge_util_hal_negative3_checkIfExistsInBridge(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64] = {"\0"};

    strcpy(iface_name, ifName);
    char *bridge_name = NULL;

    UT_LOG_DEBUG("Invoking checkIfExistsInBridge with valid interface : %s  and NULL bridge name", iface_name);
    result = checkIfExistsInBridge(iface_name, bridge_name);
    UT_LOG_DEBUG("checkIfExistsInBridge returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case to check if the interface name is empty string
 *
 * This test case checks the functionality of the checkIfExistsInBridge function when the interface name is an empty string. It verifies that the function returns -1 and the bridge name remains unchanged.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 016 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes|
 * | :--------: | --------- | ---------- | ----------| ------- |
 * | 01 | Invoke checkIfExistsInBridge with empty interface name | empty interface name | -1 | Should return error |
 */
void test_l1_bridge_util_hal_negative5_checkIfExistsInBridge(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    char iface_name[64] = "";
    char bridge_name[64] = {"\0"};

    strcpy(bridge_name, br_Name);

    UT_LOG_DEBUG("Invoking checkIfExistsInBridge with empty interface name and valid bridge : %s", bridge_name);
    result = checkIfExistsInBridge(iface_name, bridge_name);
    UT_LOG_DEBUG("checkIfExistsInBridge returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
 * @brief Test the positive scenario of the HandlePreConfigVendor function.
 *
 * This test verifies that the HandlePreConfigVendor function handles the pre-configuration vendor properly when valid configuration is provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 017 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result  | Notes|
 * | :--------: | ----------- | ---------- | ----------  | --------- |
 * | 01 | Invoking HandlePreConfigVendor with valid BridgeInfo pointer and all possible instance numbers | bridgeInfo = valid pointer, valid instance number| 0 | Should be successful |
 */
void test_l1_bridge_util_hal_positive1_HandlePreConfigVendor(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);

        UT_LOG_DEBUG("Invoking HandlePreConfigVendor with valid BridgeInfo pointer and all possible instance numbers");
        for (InstanceNumber = 1; InstanceNumber <= 14; InstanceNumber++)
        {
            if (InstanceNumber == 5)
            {
                continue;
            }
            UT_LOG_DEBUG("Invoking HandlePreConfigVendor with valid instance number : %d ", InstanceNumber);
            result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
            UT_LOG_DEBUG("HandlePreConfigVendor returns : %d", result);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);

            UT_ASSERT_EQUAL(result, 0);
        }
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This is a unit test to verify the behavior of the HandlePreConfigVendor function when NULL bridgeInfo buffer.
 *
 * This test is designed to check if the HandlePreConfigVendor function handles NULL bridgeInfo buffer and returns -1 as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 018 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke HandlePreConfigVendor with NULL bridgeInfo | bridgeInfo = NULL, valid InstanceNumber | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative1_HandlePreConfigVendor(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = NULL;

    UT_LOG_DEBUG("Invoking HandlePreConfigVendor with NULL bridgeInfo");
    result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
    UT_LOG_DEBUG("HandlePreConfigVendor returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This is a unit test to verify the behavior of the HandlePreConfigVendor function when provided with an out of range Instance number.
 *
 * This test is designed to check if the HandlePreConfigVendor function handles the out of range Instance number correctly and returns -1 as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 019 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke HandlePreConfigVendor with minimum out of range Instance number | bridgeInfo = valid pointer, InstanceNumber = 0 | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative2_HandlePreConfigVendor(void)
{
    gTestID = 19;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 0;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking HandlePreConfigVendor with minimum out of range Instance number : %d", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePreConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case to verify the behavior of HandlePreConfigVendor function when providing maximum out of range instance number.
 *
 * This test case validates the behavior of the HandlePreConfigVendor function when invoked with maximum  out of range instance number.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 020 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ------- |
 * | 01 | Invoke HandlePreConfigVendor with maximum out of range Instance number| bridgeInfo = valid pointer, InstanceNumber = 15 | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative3_HandlePreConfigVendor(void)
{
    gTestID = 20;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 15;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking HandlePreConfigVendor with maximum out of range Instance number: %d", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePreConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case to verify the behavior of HandlePreConfigVendor when a missing enum value is passed as an argument.
 *
 * This test verifies the behavior of the HandlePreConfigVendor function when a missing enum value is passed as an argument. The function should return -1 in this case.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 021 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking HandlePreConfigVendor with missing enum value | bridgeInfo = valid pointer, InstanceNumber = 5 | -1 | Should be unsuccessful  |
 */
void test_l1_bridge_util_hal_negative4_HandlePreConfigVendor(void)
{
    gTestID = 21;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 5;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking HandlePreConfigVendor with missing enum value in Instance number : %d ", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePreConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test the positive scenario of the HandlePostConfigVendor function.
 *
 * This test verifies that the HandlePostConfigVendor function handles the post-configuration vendor properly when valid configuration is provided.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 022 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result  | Notes|
 * | :--------: | ----------- | ---------- | ----------  | --------- |
 * | 01 | Invoking HandlePostConfigVendor with valid BridgeInfo pointer and all possible instance number | bridgeInfo = valid pointer, valid instance number| 0 | Should be successful |
 */
void test_l1_bridge_util_hal_positive1_HandlePostConfigVendor(void)
{
    gTestID = 22;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);

        UT_LOG_DEBUG("Invoking HandlePostConfigVendor with valid BridgeInfo pointer and all possible instance number");
        for (InstanceNumber = 1; InstanceNumber <= 14; InstanceNumber++)
        {
            if (InstanceNumber == 5)
            {
                continue;
            }
            result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
            UT_LOG_DEBUG("HandlePostConfigVendor returns : %d with Instance number : %d", result, InstanceNumber);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
            UT_ASSERT_EQUAL(result, 0);
        }
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This is a unit test to verify the behavior of the HandlePostConfigVendor function when NULL bridgeInfo buffer.
 *
 * This test is designed to check if the HandlePostConfigVendor function handles NULL bridgeInfo buffer and returns -1 as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 023 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke HandlePostConfigVendor with NULL bridgeInfo | bridgeInfo = NULL, valid InstanceNumber | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative1_HandlePostConfigVendor(void)
{
    gTestID = 23;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = NULL;

    UT_LOG_DEBUG("Invoking HandlePostConfigVendor with NULL bridgeInfo");
    result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
    UT_LOG_DEBUG("HandlePostConfigVendor returns : %d", result);
    UT_ASSERT_EQUAL(result, -1);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This is a unit test to verify the behavior of the HandlePostConfigVendor function when provided with minimum out of range Instance number.
 *
 * This test is designed to check if the HandlePostConfigVendor function handles the out of range Instance number correctly and returns -1 as expected.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 024 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke HandlePostConfigVendor with minimum out of range Instance number | bridgeInfo = valid pointer, InstanceNumber = 0 | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative2_HandlePostConfigVendor(void)
{
    gTestID = 24;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 0;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Invoking HandlePostConfigVendor with minimum out of range Instance number : %d ", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePostConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case to verify the behavior of HandlePostConfigVendor function when providing maximum out of range instance number.
 *
 * This test case validates the behavior of the HandlePostConfigVendor function when invoked with maximum  out of range instance number.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 025 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ------- |
 * | 01 | Invoke HandlePostConfigVendor with maximum out of range Instance number| bridgeInfo = valid pointer, InstanceNumber = 15 | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative3_HandlePostConfigVendor(void)
{
    gTestID = 25;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 15;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));
        UT_LOG_DEBUG("Invoking HandlePostConfigVendor with maximum out of range Instance number : %d ", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePostConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief Test case to verify the behavior of HandlePostConfigVendor when a missing enum value is passed as an argument.
 *
 * This test verifies the behavior of the HandlePostConfigVendor function when a missing enum value is passed as an argument. The function should return -1 in this case.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 026 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking HandlePostConfigVendor with missing enum value 5 | bridgeInfo = valid pointer, InstanceNumber = 5 | -1 | Should be unsuccessful |
 */
void test_l1_bridge_util_hal_negative4_HandlePostConfigVendor(void)
{
    gTestID = 26;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    InstanceNumber = 5;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        memcpy(bridgeInfo, &br_details, sizeof(br_details));

        UT_LOG_DEBUG("Invoking HandlePostConfigVendor with missing enum value in Instance number : %d", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG_DEBUG("HandlePostConfigVendor returns : %d", result);
        UT_ASSERT_EQUAL(result, -1);
        free(bridgeInfo);
    }
    else
    {
        UT_LOG_DEBUG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test function checks the validity of the vendor interface return.
 *
 * The objective of this test is to verify if the vendor interface return value is valid and meets the required conditions.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 027 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke getVendorIfaces() that provides vendor interface list| None | Non-NULL character array or NULL | Should return Interface list or NULL |
 */
void test_l1_bridge_util_hal_positive1_getVendorIfaces(void)
{
    gTestID = 27;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char vendorIfaces[64] = {"\0"};

    UT_LOG_DEBUG("Invoking getVendorIfaces API");
    char *result = getVendorIfaces();

    if (result != NULL)
    {
        if (strlen(result) < sizeof(vendorIfaces))
        {
            strcpy(vendorIfaces, result);
            UT_LOG_DEBUG("Vendor Interfaces is %s which is valid", vendorIfaces);
        }
        else
        {
            UT_LOG_DEBUG("Vendor Interfaces is too long to fit into the buffer");
        }
    }
    else
    {
        UT_LOG_DEBUG("Vendor Interface is NULL");
    }

    UT_PASS("getVendorIfaces validation success");
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
 * @brief This test case tests the functionality of the removeIfaceFromList() function.
 *
 * The objective of this test is to verify that the removeIfaceFromList() function returns the expected string after removing a sub-string from a given string.
 *
 * **Test Group ID:** Basic : 01  @n
 * **Test Case ID:** 028 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke removeIfaceFromList with valid interface name | str = valid buffer , sub = valid buffer| str should not have sub string buffer | Should be successful |
 */
void test_l1_bridge_util_hal_positive1_removeIfaceFromList(void)
{
    gTestID = 28;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char str[64] = {"\0"};

    strcpy(str, iface_to_remove);
    char sub[64] = {"\0"};

    strcpy(sub, ifName);

    UT_LOG_DEBUG("Invoking removeIfaceFromList() with valid interface name : %s and interface list : %s", sub, str);
    removeIfaceFromList(str, sub);
    if (!strstr(str, sub))
    {
        UT_LOG_DEBUG(" Interface List is %s which is a valid string", str);
        UT_PASS("removeIfaceFromList() validation success");
    }
    else
    {
        UT_LOG_DEBUG("Interface List is %s which is an invalid string", str);
        UT_FAIL("removeIfaceFromList() validation failed");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test verifies the behavior of the removeIfaceFromList() function when invoked with NULL sub parameter.
 *
 * The purpose of this test is to ensure that the function properly handles the case when the sub parameter is NULL.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 029 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description  | Test Data | Expected Result  | Notes  |
 * | :---------: | ----------| ------------- | --------------- | -------- |
 * |  01  | Invoking removeIfaceFromList() with substring as NULL  | sub = NULL | API should handle| Should be successful |
 */
void test_l1_bridge_util_hal_negative1_removeIfaceFromList(void)
{
    gTestID = 29;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char str[64] = {"\0"};

    strcpy(str, iface_to_remove);
    char *sub = NULL;

    UT_LOG_DEBUG("Invoking removeIfaceFromList() with NULL substring with interface list : %s ", str);
    removeIfaceFromList(str, sub);
    UT_LOG_DEBUG(" Interface List is %s which is a valid string", str);
    UT_PASS("removeIfaceFromList() validation success with NULL substring");

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test function tests the removeIfaceFromList() function for negative scenarios.
 *
 * The removeIfaceFromList() function is tested by passing a NULL value for the "str" argument. This test aims to ensure that the function does not crash or produce unexpected behavior when NULL is passed as input.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 030 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |  01 | Invoke removeIfaceFromList() with NULL Str | str = NULL, sub = valid buffer| Non-crashing execution | The function should not crash  |
 */
void test_l1_bridge_util_hal_negative2_removeIfaceFromList(void)
{
    gTestID = 30;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char *str = NULL;
    char sub[64] = {"\0"};

    strcpy(sub, ifName);

    UT_LOG_DEBUG("Invoking removeIfaceFromList() with NULL Str");
    removeIfaceFromList(str, sub);
    UT_PASS("removeIfaceFromList() validation success with NULL interface List");

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test case verifies the behavior of the getVendorIfaces() function when invoked with an empty sub parameter.
 *
 * The test ensures that the getVendorIfaces() function returns a non-null pointer when invoked with an empty sub parameter.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 031 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking removeIfaceFromList() with an empty sub parameter | empty sub string |Non-crashing execution | The function should not crash |
 */
void test_l1_bridge_util_hal_negative3_removeIfaceFromList(void)
{
    gTestID = 31;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char str[64] = {"\0"};

    strcpy(str, iface_to_remove);
    char sub[64] = "";

    UT_LOG_DEBUG("Invoking removeIfaceFromList() with empty substring");
    removeIfaceFromList(str, sub);
    UT_LOG_DEBUG(" Interface List is %s which is a valid string", str);
    UT_PASS("removeIfaceFromList() validation success with empty substring");

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
 * @brief This test is to verify the behavior of the removeIfaceFromList function when invoked with invalid input.
 *
 * The removeIfaceFromList function is tested with invalid input to ensure that it correctly handles invalid input and returns a non-null result.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 032 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke removeIfaceFromList function with invalid sub | invalid substring | Non-crashing execution | The function should not crash |
 */
void test_l1_bridge_util_hal_negative4_removeIfaceFromList(void)
{
    gTestID = 32;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    char str[64] = {"\0"};

    strcpy(str, iface_to_remove);
    char sub[64] = "invalid_iface";

    UT_LOG_DEBUG("Invoking removeIfaceFromList() with invalid Interface : %s ", sub);
    removeIfaceFromList(str, sub);
    UT_LOG_DEBUG(" Interface List is %s which is a valid string", str);
    UT_PASS("removeIfaceFromList() validation success with invalid substring");

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_bridge_util_hal_l1_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 bridge_util_hal]", fetch_bridge_util_details, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_updateBridgeInfo", test_l1_bridge_util_hal_positive1_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive2_updateBridgeInfo", test_l1_bridge_util_hal_positive2_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive3_updateBridgeInfo", test_l1_bridge_util_hal_positive3_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_updateBridgeInfo", test_l1_bridge_util_hal_negative1_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_updateBridgeInfo", test_l1_bridge_util_hal_negative2_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_updateBridgeInfo", test_l1_bridge_util_hal_negative3_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative4_updateBridgeInfo", test_l1_bridge_util_hal_negative4_updateBridgeInfo);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_checkIfExists", test_l1_bridge_util_hal_positive1_checkIfExists);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_checkIfExists", test_l1_bridge_util_hal_negative1_checkIfExists);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_checkIfExists", test_l1_bridge_util_hal_negative2_checkIfExists);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_checkIfExists", test_l1_bridge_util_hal_negative3_checkIfExists);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_checkIfExistsInBridge", test_l1_bridge_util_hal_positive1_checkIfExistsInBridge);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_checkIfExistsInBridge", test_l1_bridge_util_hal_negative1_checkIfExistsInBridge);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_checkIfExistsInBridge", test_l1_bridge_util_hal_negative2_checkIfExistsInBridge);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_checkIfExistsInBridge", test_l1_bridge_util_hal_negative3_checkIfExistsInBridge);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative5_checkIfExistsInBridge", test_l1_bridge_util_hal_negative5_checkIfExistsInBridge);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_HandlePreConfigVendor", test_l1_bridge_util_hal_positive1_HandlePreConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_HandlePreConfigVendor", test_l1_bridge_util_hal_negative1_HandlePreConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_HandlePreConfigVendor", test_l1_bridge_util_hal_negative2_HandlePreConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_HandlePreConfigVendor", test_l1_bridge_util_hal_negative3_HandlePreConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative4_HandlePreConfigVendor", test_l1_bridge_util_hal_negative4_HandlePreConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_HandlePostConfigVendor", test_l1_bridge_util_hal_positive1_HandlePostConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_HandlePostConfigVendor", test_l1_bridge_util_hal_negative1_HandlePostConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_HandlePostConfigVendor", test_l1_bridge_util_hal_negative2_HandlePostConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_HandlePostConfigVendor", test_l1_bridge_util_hal_negative3_HandlePostConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative4_HandlePostConfigVendor", test_l1_bridge_util_hal_negative4_HandlePostConfigVendor);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_getVendorIfaces", test_l1_bridge_util_hal_positive1_getVendorIfaces);
    UT_add_test(pSuite, "l1_bridge_util_hal_positive1_removeIfaceFromList", test_l1_bridge_util_hal_positive1_removeIfaceFromList);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative1_removeIfaceFromList", test_l1_bridge_util_hal_negative1_removeIfaceFromList);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative2_removeIfaceFromList", test_l1_bridge_util_hal_negative2_removeIfaceFromList);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative3_removeIfaceFromList", test_l1_bridge_util_hal_negative3_removeIfaceFromList);
    UT_add_test(pSuite, "l1_bridge_util_hal_negative4_removeIfaceFromList", test_l1_bridge_util_hal_negative4_removeIfaceFromList);
    return 0;
}