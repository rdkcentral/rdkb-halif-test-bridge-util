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
* @file test_bridge_util_hal.c
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

/**
* @brief Test the positive scenario of the HandlePreConfigVendor function.
*
* This test verifies that the HandlePreConfigVendor function handles the pre-configuration vendor properly when valid configuration is provided.
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
* | Variation / Step | Description | Test Data | Expected Result  | Notes|
* | :--------: | ----------- | ---------- | ----------  | --------- |
* | 01 | Invoking HandlePreConfigVendor with valid BridgeInfo pointer and all possible instance numbers | bridgeInfo = valid pointer, valid instance number| 0 | Should be successful |
*/
void test_l1_bridge_util_hal_positive1_HandlePreConfigVendor(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_positive1_HandlePreConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 1;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        UT_LOG("Invoking HandlePreConfigVendor with valid BridgeInfo pointer and all possible instance numbers");
        for( InstanceNumber = 1; InstanceNumber <= 14 ; InstanceNumber++)
        {
            if (InstanceNumber == 5)
            {
                 continue;
            }
            result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
            UT_LOG("HandlePreConfigVendor returns : %d", result);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
            UT_LOG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);
            UT_ASSERT_EQUAL(result, 0);
        }

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_positive1_HandlePreConfigVendor...");
}

/**
* @brief This is a unit test to verify the behavior of the HandlePreConfigVendor function when NULL bridgeInfo buffer.
*
* This test is designed to check if the HandlePreConfigVendor function handles NULL bridgeInfo buffer and returns -1 as expected.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke HandlePreConfigVendor with NULL bridgeInfo | bridgeInfo = NULL, valid InstanceNumber | -1 | Should be unsuccessful |
*/
void test_l1_bridge_util_hal_negative1_HandlePreConfigVendor(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_negative1_HandlePreConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = NULL;  
    int InstanceNumber = 1;  

    UT_LOG("Invoking HandlePreConfigVendor with NULL bridgeInfo");
    result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
    UT_LOG("HandlePreConfigVendor returns : %d", result);    
    UT_ASSERT_EQUAL(result, -1);
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative1_HandlePreConfigVendor...");
}
/**
* @brief This is a unit test to verify the behavior of the HandlePreConfigVendor function when provided with an out of range Instance number.
*
* This test is designed to check if the HandlePreConfigVendor function handles the out of range Instance number correctly and returns -1 as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 003 @n
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
    UT_LOG("Entering test_l1_bridge_util_hal_negative2_HandlePreConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 0;
    if (bridgeInfo != NULL)
    {    
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        UT_LOG("Invoking HandlePreConfigVendor with minimum out of range Instance number : %d", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePreConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative2_HandlePreConfigVendor...");
}

/**
* @brief Test case to verify the behavior of HandlePreConfigVendor function when providing maximum out of range instance number.
*
* This test case validates the behavior of the HandlePreConfigVendor function when invoked with maximum  out of range instance number.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 004 @n
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
    UT_LOG("Entering test_l1_bridge_util_hal_negative3_HandlePreConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 15;
    if (bridgeInfo != NULL)
    {  
        memset(bridgeInfo, 0, sizeof(bridgeDetails));  
        UT_LOG("Invoking HandlePreConfigVendor with maximum out of range Instance number: %d", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePreConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative3_HandlePreConfigVendor...");
}

/**
* @brief Test case to verify the behavior of HandlePreConfigVendor when a missing enum value is passed as an argument.
*
* This test verifies the behavior of the HandlePreConfigVendor function when a missing enum value is passed as an argument. The function should return -1 in this case.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 005 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking HandlePreConfigVendor with missing enum value | bridgeInfo = valid pointer, configValue = 5 | -1 | Should be unsuccessful  |
*/
void test_l1_bridge_util_hal_negative4_HandlePreConfigVendor(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_negative4_HandlePreConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 5;
    if (bridgeInfo != NULL)
    { 
        memset(bridgeInfo, 0, sizeof(bridgeDetails));   
        UT_LOG("Invoking HandlePreConfigVendor with missing enum value in Instance number : %d ", InstanceNumber);
        result = HandlePreConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePreConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
        
    UT_LOG("Exiting test_l1_bridge_util_hal_negative4_HandlePreConfigVendor...");
}

/**
* @brief Test the positive scenario of the HandlePostConfigVendor function.
*
* This test verifies that the HandlePostConfigVendor function handles the post-configuration vendor properly when valid configuration is provided.
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
* | Variation / Step | Description | Test Data | Expected Result  | Notes|
* | :--------: | ----------- | ---------- | ----------  | --------- |
* | 01 | Invoking HandlePostConfigVendor with valid BridgeInfo pointer and all possible instance number | bridgeInfo = valid pointer, valid instance number| 0 | Should be successful |
*/
void test_l1_bridge_util_hal_positive1_HandlePostConfigVendor(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_positive1_HandlePostConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 1;
    if (bridgeInfo != NULL)
    {
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        UT_LOG("Invoking HandlePostConfigVendor with valid BridgeInfo pointer and all possible instance number");
        for( InstanceNumber = 1; InstanceNumber <= 14 ; InstanceNumber++)
        {
            if (InstanceNumber == 5)
            {
                 continue;
            }
            result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
            UT_LOG("HandlePostConfigVendor returns : %d with Instance number : %d", result, InstanceNumber);
            UT_ASSERT_PTR_NOT_NULL(bridgeInfo);
            UT_LOG("Bridge Details - bridgeName : %s , vlan_name : %s , VirtualParentIfname : %s ,vlanID : %d , ethIfList : %s, MoCAIfList : %s, GreIfList : %s, WiFiIfList : %s", bridgeInfo->bridgeName, bridgeInfo->vlan_name, bridgeInfo->VirtualParentIfname, bridgeInfo->vlanID, bridgeInfo->ethIfList, bridgeInfo->MoCAIfList, bridgeInfo->GreIfList, bridgeInfo->WiFiIfList);
            UT_ASSERT_EQUAL(result, 0);
        }

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_positive1_HandlePostConfigVendor...");
}

/**
* @brief This is a unit test to verify the behavior of the HandlePostConfigVendor function when NULL bridgeInfo buffer.
*
* This test is designed to check if the HandlePostConfigVendor function handles NULL bridgeInfo buffer and returns -1 as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 007 @n
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
    UT_LOG("Entering test_l1_bridge_util_hal_negative1_HandlePostConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = NULL;  
    int InstanceNumber = 1;  

    UT_LOG("Invoking HandlePostConfigVendor with NULL bridgeInfo");
    result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
    UT_LOG("HandlePostConfigVendor returns : %d", result);    
    UT_ASSERT_EQUAL(result, -1);
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative1_HandlePostConfigVendor...");
}

/**
* @brief This is a unit test to verify the behavior of the HandlePostConfigVendor function when provided with minimum out of range Instance number.
*
* This test is designed to check if the HandlePostConfigVendor function handles the out of range Instance number correctly and returns -1 as expected.
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
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke HandlePostConfigVendor with minimum out of range Instance number | bridgeInfo = valid pointer, InstanceNumber = 0 | -1 | Should be unsuccessful |
*/
void test_l1_bridge_util_hal_negative2_HandlePostConfigVendor(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_negative2_HandlePostConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 0;
    if (bridgeInfo != NULL)
    {  
        memset(bridgeInfo, 0, sizeof(bridgeDetails));  
        UT_LOG("Invoking HandlePostConfigVendor with minimum out of range Instance number : %d ", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePostConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative2_HandlePostConfigVendor...");
}

/**
* @brief Test case to verify the behavior of HandlePostConfigVendor function when providing maximum out of range instance number.
*
* This test case validates the behavior of the HandlePostConfigVendor function when invoked with maximum  out of range instance number.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 009 @n
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
    UT_LOG("Entering test_l1_bridge_util_hal_negative3_HandlePostConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 15;
    if (bridgeInfo != NULL)
    {    
        memset(bridgeInfo, 0, sizeof(bridgeDetails));
        UT_LOG("Invoking HandlePostConfigVendor with maximum out of range Instance number : %d ", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePostConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_bridge_util_hal_negative3_HandlePostConfigVendor...");
}

/**
* @brief Test case to verify the behavior of HandlePostConfigVendor when a missing enum value is passed as an argument.
*
* This test verifies the behavior of the HandlePostConfigVendor function when a missing enum value is passed as an argument. The function should return -1 in this case.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 010 @n
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
    UT_LOG("Entering test_l1_bridge_util_hal_negative4_HandlePostConfigVendor...");
    int result = 0;
    bridgeDetails *bridgeInfo = (bridgeDetails *)malloc(sizeof(bridgeDetails));   
    int InstanceNumber = 5;
    if (bridgeInfo != NULL)
    { 
        memset(bridgeInfo, 0, sizeof(bridgeDetails));   
        UT_LOG("Invoking HandlePostConfigVendor with missing enum value in Instance number : %d", InstanceNumber);
        result = HandlePostConfigVendor(bridgeInfo, InstanceNumber);
        UT_LOG("HandlePostConfigVendor returns : %d", result);    
        UT_ASSERT_EQUAL(result, -1);

        free(bridgeInfo);
        bridgeInfo = NULL;
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
        
    UT_LOG("Exiting test_l1_bridge_util_hal_negative4_HandlePostConfigVendor...");
}

/**
* @brief This test function checks the validity of the vendor interface return.
*
* The objective of this test is to verify if the vendor interface return value is valid and meets the required conditions.
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
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke getVendorIfaces() that provides vendor interface list| None | Non-NULL character array or NULL | Should return Interface list or NULL |
*/
void test_l1_bridge_util_hal_positive1_getVendorIfaces(void) 
{
    UT_LOG("Entering test_l1_bridge_util_hal_positive1_getVendorIfaces...");
    char vendorIfaces[64] =  {"\0"}; 

    UT_LOG("Invoking getVendorIfaces API");
    char *result = getVendorIfaces();
    
    if (result != NULL) 
    {
        if (strlen(result) < sizeof(vendorIfaces))
        {
            strcpy(vendorIfaces, result);
            UT_LOG("Vendor Interfaces is %s which is valid", vendorIfaces);
        }
        else
        {
            UT_LOG("Vendor Interfaces is too long to fit into the buffer");
        }
    }
    else
    { 
        UT_LOG("Vendor Interface is NULL");
    }
    
    UT_PASS("getVendorIfaces validation success");
    UT_LOG("Exiting test_l1_bridge_util_hal_positive1_getVendorIfaces...");
}


static UT_test_suite_t * pSuite = NULL;

/**
* @brief Register the main tests for this module
*
* @return int - 0 on success, otherwise failure
*/
int register_hal_tests(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 bridge_util_hal]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings
   const char* list1[] = {"l1_bridge_util_hal_positive1_HandlePreConfigVendor", "l1_bridge_util_hal_negative1_HandlePreConfigVendor", "l1_bridge_util_hal_negative2_HandlePreConfigVendor", "l1_bridge_util_hal_negative3_HandlePreConfigVendor", "l1_bridge_util_hal_negative4_HandlePreConfigVendor","l1_bridge_util_hal_positive1_HandlePostConfigVendor","l1_bridge_util_hal_negative1_HandlePostConfigVendor", "l1_bridge_util_hal_negative2_HandlePostConfigVendor","l1_bridge_util_hal_negative3_HandlePostConfigVendor","l1_bridge_util_hal_negative4_HandlePostConfigVendor","l1_bridge_util_hal_positive1_getVendorIfaces"};
   void (*list2[])() = { test_l1_bridge_util_hal_positive1_HandlePreConfigVendor, test_l1_bridge_util_hal_negative1_HandlePreConfigVendor, test_l1_bridge_util_hal_negative2_HandlePreConfigVendor, test_l1_bridge_util_hal_negative3_HandlePreConfigVendor, test_l1_bridge_util_hal_negative4_HandlePreConfigVendor, test_l1_bridge_util_hal_positive1_HandlePostConfigVendor, test_l1_bridge_util_hal_negative1_HandlePostConfigVendor,test_l1_bridge_util_hal_negative2_HandlePostConfigVendor,test_l1_bridge_util_hal_negative3_HandlePostConfigVendor,test_l1_bridge_util_hal_negative4_HandlePostConfigVendor,test_l1_bridge_util_hal_positive1_getVendorIfaces};
    // Add tests to the suite
    for (int i = 0; i < sizeof(list1) / sizeof(list1[0]); i++) {
        UT_add_test(pSuite, list1[i], list2[i]);
    }
    return 0;
}
int main(int argc, char** argv)
{
    int registerReturn = 0;
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_tests() returned success");
    }
    else
    {
        printf("register_hal_tests() returned failure");
        return 1;
    }
    /* Begin test executions */
    UT_run_tests();
    return 0;
}