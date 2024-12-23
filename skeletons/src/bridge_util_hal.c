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
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "bridge_util_hal.h"

int __attribute__((weak)) updateBridgeInfo(bridgeDetails *bridgeInfo, char *ifNameToBeUpdated, int Opr, int type)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)ifNameToBeUpdated;
  (void)Opr;
  (void)type;
  return (int)0;
}

int __attribute__((weak)) checkIfExists(char *iface_name)
{
  /*TODO: Implement Me!*/
  (void)iface_name;
  return (int)0;
}

void __attribute__((weak)) removeIfaceFromList(char *str, const char *sub)
{
  /*TODO: Implement Me!*/
  (void)str;
  (void)sub;
}

int __attribute__((weak)) checkIfExistsInBridge(char *iface_name, char *bridge_name)
{
  /*TODO: Implement Me!*/
  (void)iface_name;
  (void)bridge_name;
  return (int)0;
}

int __attribute__((weak)) HandlePreConfigVendor(bridgeDetails *bridgeInfo, int InstanceNumber)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)InstanceNumber;
  return (int)0;
}

int __attribute__((weak)) HandlePostConfigVendor(bridgeDetails *bridgeInfo, int Config)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)Config;
  return (int)0;
}

char __attribute__((weak)) * getVendorIfaces(void)
{
  /*TODO: Implement Me!*/
  return (char *)0;
}
