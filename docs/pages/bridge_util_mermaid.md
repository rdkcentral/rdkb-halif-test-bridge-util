Please find the mermaid flow of Bridge Util L2 Test cases:

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_VLAN_Type

```mermaid
flowchart TD
A[Start] --> B[Create bridge 'brlan100' with updateBridgeInfo]
B -- Success --> C[Create interface 'link100' on 'brlan100' with updateBridgeInfo]
B -- Failure --> F[Test Case Fail at Step 1: Bridge Creation]
C -- Success --> D[Call checkIfExistsInBridge for 'link100' in 'brlan100']
C -- Failure --> G[Test Case Fail at Step 2: Interface Creation]
D -- Returns 0 --> E[Delete interface 'link100' on 'brlan100' with updateBridgeInfo]
D -- Does not return 0 --> H[Test Case Fail at Step 3: Check Interface Existence]
E -- Success --> I[Call checkIfExistsInBridge for 'link100' in 'brlan100']
E -- Failure --> J[Test Case Fail at Step 4: Interface Deletion]
I -- Returns -1 --> K[Delete bridge 'brlan100' with updateBridgeInfo]
I -- Does not return -1 --> L[Test Case Fail at Step 5: Check Interface Deletion]
K -- Success --> M[End]
K -- Failure --> N[Test Case Fail at Step 6: Bridge Deletion]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_WIFI_Type

```mermaid
flowchart TD
A[Start] --> B[Create bridge 'brlan100']
B -- Success --> C["Create WiFi interface with WiFiIfList {wifi100, wifi101, wifi102}"]
B -- Failure --> F[Test Case Fail at Step 1: Bridge Creation]
C -- Success --> D[Check if 'wifi100' exists in 'brlan100']
C -- Failure --> G[Test Case Fail at Step 2: WiFi Interface Creation]
D -- Returns 0 --> E["Delete WiFi interface with WiFiIfList {wifi100, wifi101, wifi102}"]
D -- Does not return 0 --> H[Test Case Fail at Step 3: Check WiFi Interface Existence]
E -- Success --> I[Check if 'wifi100' does not exist in 'brlan100']
E -- Failure --> J[Test Case Fail at Step 4: WiFi Interface Deletion]
I -- Returns -1 --> K[Delete bridge 'brlan100']
I -- Does not return -1 --> L[Test Case Fail at Step 5: Check WiFi Interface Deletion]
K -- Success --> M[End]
K -- Failure --> N[Test Case Fail at Step 6: Bridge Deletion]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_MOCA_Type

```mermaid
flowchart TD
A[Start] --> B[Create bridge 'brlan100']
B -- Success --> C["Create MoCA interface with MoCAIfList {moca100, moca101, moca102}"]
B -- Failure --> F[Test Case Fail at Step 1: Bridge Creation]
C -- Success --> D[Check if 'moca100' exists in 'brlan100']
C -- Failure --> G[Test Case Fail at Step 2: MoCA Interface Creation]
D -- Returns 0 --> E["Delete MoCA interface with MoCAIfList {moca100, moca101, moca102}"]
D -- Does not return 0 --> H[Test Case Fail at Step 3: Check MoCA Interface Existence]
E -- Success --> I[Check if 'moca100' does not exist in 'brlan100']
E -- Failure --> J[Test Case Fail at Step 4: MoCA Interface Deletion]
I -- Returns -1 --> K[Delete bridge 'brlan100']
I -- Does not return -1 --> L[Test Case Fail at Step 5: Check MoCA Interface Deletion]
K -- Success --> M[End]
K -- Failure --> N[Test Case Fail at Step 6: Bridge Deletion]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_GRE_Type

```mermaid
flowchart TD
A[Start] --> B[Create bridge 'brlan100']
B -- Success --> C["Create GRE interface with GreIfList {gre100, gre101, gre102}"]
B -- Failure --> F[Test Case Fail at Step 1: Bridge Creation]
C -- Success --> D[Check if 'gre100' exists in 'brlan100']
C -- Failure --> G[Test Case Fail at Step 2: GRE Interface Creation]
D -- Returns 0 --> E["Delete GRE interface with GreIfList {gre100, gre101, gre102}"]
D -- Does not return 0 --> H[Test Case Fail at Step 3: Check GRE Interface Existence]
E -- Success --> I[Check if 'gre100' does not exist in 'brlan100']
E -- Failure --> J[Test Case Fail at Step 4: GRE Interface Deletion]
I -- Returns -1 --> K[Delete bridge 'brlan100']
I -- Does not return -1 --> L[Test Case Fail at Step 5: Check GRE Interface Deletion]
K -- Success --> M[End]
K -- Failure --> N[Test Case Fail at Step 6: Bridge Deletion]
```

### Test Function Name : test_l2_bridge_util_hal_updateAndCheckInBridge_IF_ETH_Type

```mermaid
flowchart TD
A[Start] --> B[Create bridge 'brlan100']
B -- Success --> C["Create eth interface with ethIfList {eth100, eth101, eth102}"]
B -- Failure --> F[Test Case Fail at Step 1: Bridge Creation]
C -- Success --> D[Check if 'eth100' exists in 'brlan100']
C -- Failure --> G[Test Case Fail at Step 2: eth Interface Creation]
D -- Returns 0 --> E["Delete eth interface with ethIfList {eth100, eth101, eth102}"]
D -- Does not return 0 --> H[Test Case Fail at Step 3: Check eth Interface Existence]
E -- Success --> I[Check if 'eth100' does not exist in 'brlan100']
E -- Failure --> J[Test Case Fail at Step 4: eth Interface Deletion]
I -- Returns -1 --> K[Delete bridge 'brlan100']
I -- Does not return -1 --> L[Test Case Fail at Step 5: Check eth Interface Deletion]
K -- Success --> M[End]
K -- Failure --> N[Test Case Fail at Step 6: Bridge Deletion]
```