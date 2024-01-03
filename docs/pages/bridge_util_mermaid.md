Please find the mermaid flow of Bridge Util L2 Test cases:

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_VLAN_Type

```mermaid
graph TB
A[Start] --> B[Create a bridge using updateBridgeInfo]
B --> C[Create an interface to the same bridge using updateBridgeInfo]
C --> D[Call checkIfExistsInBridge api for the created interface and bridge]
D --> |Returns 0| E[Delete the interface on the same bridge using updateBridgeInfo]
E --> F[Call checkIfExistsInBridge for the deleted interface and bridge]
F --> |Returns -1| G[Delete the bridge using updateBridgeInfo]
G --> H[End]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_WIFI_Type

```mermaid
graph TB
A[Start] --> B(Create bridgeDetails using updateBridgeInfo with bridgeName, Opr, type)
B --> C(Create interface to the bridge using updateBridgeInfo with WiFiIfList, ifNameToBeUpdated, Opr, type)
C --> D[Call checkIfExistsInBridge with iface_name, bridge_name]
D -- If returns 0 --> E(Delete interface on the bridge using updateBridgeInfo with WiFiIfList, ifNameToBeUpdated, Opr, type)
E --> F[Call checkIfExistsInBridge with iface_name, bridge_name]
F -- If returns -1 --> G(Delete the bridge using updateBridgeInfo with bridgeName, ifNameToBeUpdated, Opr, type)
G --> H[End]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_MOCA_Type

```mermaid
graph TB
start[start] --> step1[Create Bridge using updateBridgeInfo]
step1 --> step2[Create moca interface on bridge using updateBridgeInfo]
step2 --> cond1{moca100 exists \n on bridge?}
cond1 --Yes--> step4[Delete moca interfaces using updateBridgeInfo]
cond1 --No -->Step8[End]
step4 --> cond2{moca100 exists \n on bridge?}
cond2 --No --> step6[Delete bridge using updateBridgeInfo]
cond2 -- Yes --> Step9[End]
step6 --> step7[End]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_GRE_Type

```mermaid
graph TD
A["Create bridgeDetails structure using updateBridgeInfo with brlan100"]
B["Create an interface to same bridge using updateBridgeInfo with GreIfList as {gre100, gre101, gre102}" ]
C["Call checkIfExistsInBridge api with iface_name as gre100 and bridge_name as brlan100"]
D["Delete the interface on same bridge using updateBridgeInfo "]
E["Call checkIfExistsInBridge api with iface_name as gre100"]
F["Delete the bridge using updateBridgeInfo"]
A --> B
B --returns 0 --> C
C --> D
D --> E
E --returns -1 --> F
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_ETH_Type

```mermaid
graph TD
A[Start] --> B[bridgeDetails structure creation using updateBridgeInfo]
B --> C["Create interface to bridge using updateBridgeInfo with EthIfList"]
C --> D["Call checkIfExistsInBridge with eth100, brlan100"]
D --> |"Returns 0"| E["Delete the eth100 interface using updateBridgeInfo"]
E --> F["Call checkIfExistsInBridge with eth100, brlan100"]
F --> |"Returns -1"| G["Delete the bridge using updateBridgeInfo"]
G --> H[End]
```