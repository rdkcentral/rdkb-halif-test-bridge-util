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
#include "bridge_util_hal.h"

int DeviceMode = 0;
int need_wifi_gw_refresh = 0;
int need_switch_gw_refresh = 0;
int syncMembers = 0;
int BridgeOprInPropgress = 0;
FILE *logFp = NULL;
char log_buff[MAX_LOG_BUFF_SIZE] = {0};
char log_msg_wtime[MAX_LOG_BUFF_SIZE + TIMESTAMP] = {0};
char primaryBridgeName[64] = {0};
int ethWanEnabled = 0;
char ethWanIfaceName[64] = "eth0";
struct tm *timeinfo = NULL;
time_t utc_time = 0;
