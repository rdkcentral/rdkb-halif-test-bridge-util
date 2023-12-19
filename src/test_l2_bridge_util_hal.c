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
* @file test_l2_bridge_util_hal.c
* @page bridge_util_hal Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
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

/**
* @brief This test checks the functionality of the bridge info update and verification for vlan interface.
*
* This unit test ensures that the L2 bridge utility updateBridgeInfo function works as expected, and that the checkIfExistsInBridge function correctly verifies the existence of an interface in a bridge. Both 'create' and 'delete' operations are tested for updating the bridge info, followed by the it's necessary validation.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_module_test_specification.md](l2_module_test_specification.md)
*/
void test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan( void )
{
    UT_LOG("Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan...\n");
    int result = 0;
    char ifNameToBeUpdated[64] =  {"\0"};
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));

        strcpy(bridgeInfo->bridgeName,"brlan100");
        OVS_CMD Opr = OVS_BRIDGE_IF_TYPE;
        OVS_IF_TYPE type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(bridgeInfo->vlan_name,"link100");
        bridgeInfo->vlanID = 100;
        Opr = OVS_IF_UP_CMD;
        type = IF_VLAN_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new interface to the bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and interface");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, bridgeInfo->vlan_name);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_VLAN_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting interface");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and vlan interface not exist ");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, bridgeInfo->vlan_name);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, -1);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_ASSERT_EQUAL(result, 0);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan...\n");
}

/**
* @brief Testing the creation, update, and deletion of bridges and wifi interfaces in the L2 module.
*
* This unit test aims to verify the correct functionality of creating, updating, and deleting bridges and interfaces. The test sequentially creates a bridge, updates the bridge information, checks if the updated information exists in the bridge, and finally deletes the interface. The purpose of this test is to ensure that the L2 module behaves as expected when performing these operations, which are integral to the module's fundamental operations.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_module_test_specification.md](l2_module_test_specification.md)
*/
void test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi( void )
{
    UT_LOG("Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi...");
    int result = 0;
    char ifNameToBeUpdated[64] =  {"\0"};
    char interface[64] =  {"\0"};
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));

        strcpy(bridgeInfo->bridgeName,"brlan100");
        OVS_CMD Opr = OVS_BRIDGE_IF_TYPE;
        OVS_IF_TYPE type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(bridgeInfo->WiFiIfList,"wifi100  wifi101 wifi102");
        bridgeInfo->vlanID = 100;
        Opr = OVS_IF_UP_CMD;
        type = IF_WIFI_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new wifi Interface list to the bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(interface, "wifi100");
        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and interface");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName,interface );
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_WIFI_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting interface");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and wifi interface not exist ");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, interface);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, -1);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_ASSERT_EQUAL(result, 0);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi...\n");
}

/**
* @brief Tests if an interface exists in the bridge through the L2 HAL API function
*
* Performs a check on the L2 HAL function 'updateBridgeInfo' and 'checkIfExistsInBridge' to create a bridge and moca interfaceand subsequently verify their existence. In addition, tests the functionality of deleting the created bridge and interfaces to ensure that the necessary resources are cleaned up correctly after the test.
*
* **Test Group ID:** 02 (Module Integration)
* **Test Case ID:** 003
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_module_test_specification.md](l2_module_test_specification.md)
*/
void test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca( void )
{
    UT_LOG("Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca...");
    int result = 0;
    char ifNameToBeUpdated[64] =  {"\0"};
    char interface[64] =  {"\0"};
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));

        strcpy(bridgeInfo->bridgeName,"brlan100");
        OVS_CMD Opr = OVS_BRIDGE_IF_TYPE;
        OVS_IF_TYPE type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(bridgeInfo->MoCAIfList,"moca100  moca101 moca102");
        bridgeInfo->vlanID = 100;
        Opr = OVS_IF_UP_CMD;
        type = IF_MOCA_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new moca Interface list to the bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(interface, "moca100");
        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and interface");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName,interface );
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_MOCA_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting interface");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and moca interface not exist ");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, interface);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, -1);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_ASSERT_EQUAL(result, 0);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca...\n");
}

/**
* @brief Tests the functionality of the l2 bridge utility's functions: createBridge, updateBridgeInfo, and checkIfExistsInBridge
*
* This unit test aims to validate the proper functioning and integration of the l2 bridge utility's methods createBridge, updateBridgeInfo, and checkIfExistsInBridge. The methods are tested under multiple update and check conditions to confirm the accuracy and robustness of their implementations.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_module_test_specification.md](l2_module_test_specification.md)
*/
void test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre( void )
{
    UT_LOG("Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre...");
    int result = 0;
    char ifNameToBeUpdated[64] =  {"\0"};
    char interface[64] =  {"\0"};
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));

        strcpy(bridgeInfo->bridgeName,"brlan100");
        OVS_CMD Opr = OVS_BRIDGE_IF_TYPE;
        OVS_IF_TYPE type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(bridgeInfo->MoCAIfList,"gre100 gre101 gre102");
        bridgeInfo->vlanID = 100;
        Opr = OVS_IF_UP_CMD;
        type = IF_GRE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new gre Interface list to the bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(interface, "gre100");
        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and gre interface");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName,interface );
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_GRE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting gre interface");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and gre interface not exist ");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, interface);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, -1);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_ASSERT_EQUAL(result, 0);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre...\n");
}

/**
* @brief Test to check the functionality of the L2 bridge utility HAL
*
* This test is designed to check if the interface exists in the bridge and to update the bridge information correctly. It focuses on testing the 'createInterface', 'checkIfExistsInBridge' and 'updateBridgeInfo'functions of the L2 bridge utility HAL.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_module_test_specification.md](l2_module_test_specification.md)
*/
void test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth( void )
{
    UT_LOG("Entering test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth...");
    int result = 0;
    char ifNameToBeUpdated[64] =  {"\0"};
    char interface[64] =  {"\0"};
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));

        strcpy(bridgeInfo->bridgeName,"brlan100");
        OVS_CMD Opr = OVS_BRIDGE_IF_TYPE;
        OVS_IF_TYPE type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(bridgeInfo->MoCAIfList,"eth100 eth101 eth102");
        bridgeInfo->vlanID = 100;
        Opr = OVS_IF_UP_CMD;
        type = IF_ETH_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for creating new eth Interface list to the bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        strcpy(interface, "eth100");
        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and eth interface");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName,interface );
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_ETH_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting eth interface");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_LOG(" updateBridgeInfo returns: %d",result);
        UT_ASSERT_EQUAL(result, 0);

        UT_LOG("Invoking checkIfExistsInBridge with valid bridge and eth interface not exist ");
        result = checkIfExistsInBridge(bridgeInfo->bridgeName, interface);
        UT_LOG(" checkIfExistsInBridge returns: %d",result);
        UT_ASSERT_EQUAL(result, -1);

        Opr = OVS_IF_DELETE_CMD;
        type = IF_BRIDGE_BRIDGEUTIL;
        UT_LOG("Invoking updateBridgeInfo for deleting bridge");
        result = updateBridgeInfo(bridgeInfo, ifNameToBeUpdated, Opr, type);
        UT_ASSERT_EQUAL(result, 0);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth...\n");
}


static UT_test_suite_t * pSuite = NULL;

/**
* @brief Register the main tests for this module
*
* @return int - 0 on success, otherwise failure
*/

int test_bridge_util_hal_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 bridge_util_hal]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings
    UT_add_test( pSuite, "l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan", test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_vlan);
    UT_add_test( pSuite, "l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi", test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_wifi);
    UT_add_test( pSuite, "l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca", test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_moca);
    UT_add_test( pSuite, "l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre", test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_gre);
    UT_add_test( pSuite, "l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth", test_l2_bridge_util_hal_updateBridgeInfo_checkIfExistsInBridge_eth);

    return 0;
}