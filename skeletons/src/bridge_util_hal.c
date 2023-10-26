#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "bridge_util_hal.h"

int updateBridgeInfo(bridgeDetails* bridgeInfo, char* ifNameToBeUpdated, int Opr, int type)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)ifNameToBeUpdated;
  (void)Opr;
  (void)type;
  return (int)0;
}

int checkIfExists(char* iface_name)
{
  /*TODO: Implement Me!*/
  (void)iface_name;
  return (int)0;
}

void removeIfaceFromList(char* str, const char* sub)
{
  /*TODO: Implement Me!*/
  (void)str;
  (void)sub;
}

int checkIfExistsInBridge(char* iface_name, char* bridge_name)
{
  /*TODO: Implement Me!*/
  (void)iface_name;
  (void)bridge_name;
  return (int)0;
}

int HandlePreConfigVendor(bridgeDetails* bridgeInfo, int InstanceNumber)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)InstanceNumber;
  return (int)0;
}

int HandlePostConfigVendor(bridgeDetails* bridgeInfo, int Config)
{
  /*TODO: Implement Me!*/
  (void)bridgeInfo;
  (void)Config;
  return (int)0;
}

char* getVendorIfaces(void)
{
  /*TODO: Implement Me!*/
  return (char*)0;
}

