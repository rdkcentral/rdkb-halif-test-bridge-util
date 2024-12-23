# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2023 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
TOP_DIR := $(ROOT_DIR)
SRC_DIRS = $(ROOT_DIR)/src
INC_DIRS := $(ROOT_DIR)/../include
HAL_LIB_DIR := $(ROOT_DIR)/libs

HAL_LIB := bridge_utils

XCFLAGS := -DNDEBUG

TARGET_EXEC := bridgeutil_hal_test

BUILD_WEAK_STUBS_SRC = $(ROOT_DIR)/skeletons/src

ifeq ($(TARGET),)
$(info TARGET NOT SET)
$(info TARGET FORCED TO Linux)
TARGET = linux
CFLAGS += -DBUILD_LINUX
endif


$(info TARGET [$(TARGET)])

ifeq ($(TARGET),arm)
YLDFLAGS = -Wl,-rpath,$(HAL_LIB_DIR) -L$(HAL_LIB_DIR) -l$(HAL_LIB)
endif


.PHONY: clean list all


export YLDFLAGS
export BIN_DIR
export SRC_DIRS
export INC_DIRS
export TARGET
export TOP_DIR
export HAL_LIB_DIR
export XCFLAGS
export CFLAGS
export TARGET_EXEC
export BUILD_WEAK_STUBS_SRC

.PHONY: clean list build

build: 
	@echo UT [$@]
	make -C ./ut-core

list:
	@echo UT [$@]
	make -C ./ut-core list

clean:
	@echo UT [$@]
	make -C ./ut-core cleanall


