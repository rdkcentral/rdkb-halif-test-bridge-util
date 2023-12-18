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

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include "bridge_util_hal.h"

extern char ifaceName[64];
extern char bridgeName[64];
extern char interfaceList[64];

extern int register_hal_l1_tests( void );

extern int get_ifaceName(void);
extern int get_bridgeName(void);
extern int get_interfaceList(void);

int main(int argc, char** argv)
{
    int registerReturn = 0;
    if (get_ifaceName() == 0)
    {
        UT_LOG("Got the Interface Name value : %s", ifaceName);
    }
    else
    {
        printf("Failed to get Interface Name value\n");
    }
    if (get_bridgeName() == 0)
    {
        UT_LOG("Got the bridge name value : %s", bridgeName);
    }
    else
    {
        printf("Failed to get bridge name value\n");
    }
    if (get_interfaceList() == 0)
    {
        UT_LOG("Got the interface List value : %s", interfaceList);
    }
    else
    {
        printf("Failed to get interface List value\n");
    }
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_l1_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_l1_tests() returned success");
    }
    else
    {
        printf("register_hal_l1_tests() returned failure");
        return 1;
    }

    /* Begin test executions */
    UT_run_tests();

    return 0;
}