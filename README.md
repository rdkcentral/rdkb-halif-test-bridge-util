# Unit Testing Suite For Bridge-util HAL

The following documents should be referenced to provide specific information on the tests required for this module.
[Documentation can be found under "docs/pages" in this repository](docs/pages)

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)

## Acronyms, Terms and Abbreviations

- `L1` - Unit Tests
- `HAL`- Hardware Abstraction Layer

## Description

This repository contains the Unit Test Suites (L1) for bridge-util `HAL`.


### Build the linux environment from hal repo :

- For compiling vendor specific APIs :

```bash
./build_ut.sh
```

- For compiling generic APIs and vendor specific APIs :

```bash
./build_ut.sh ENABLE_RDKBHAL_TEST=1
```

### Build the target `crosscompile` environment from hal repo :

Set the crosscompile environment

- For compiling vendor specific APIs :
```bash
./build_ut.sh TARGET=`crosscompile`
```

- For compiling generic APIs and vendor specific APIs :

```bash
./build_ut.sh TARGET=`crosscompile` ENABLE_RDKBHAL_TEST=1
```
let `crosscompile' is the target environment like arm

## Reference Documents

<!-- Need to update links to point to correct repo -->
|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|`HAL` Specification Document|This document provides specific information on the APIs for which tests are written in this module|[BridgeUtilHalSpec.md](https://github.com/rdkcentral/rdkb-halif-bridge-util/blob/main/docs/pages/BridgeUtilHalSpec.md "BridgeUtilHalSpec.md" )|
|3|`L1` Tests | `L1` Test Case File for this module |[test_l1_bridge_util_hal.c](src/test_l1_bridge_util_hal "test_l1_bridge_util_hal.c" )|
