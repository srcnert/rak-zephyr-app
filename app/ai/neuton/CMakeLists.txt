# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(neuton-rak1904)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/neuton-ai/neuton/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/neuton-ai)

target_sources(app PRIVATE src/main.c)

# Add neuton-ai project files
zephyr_include_directories(neuton-ai)
zephyr_include_directories(neuton-ai/neuton/include)
zephyr_link_libraries(${CMAKE_CURRENT_LIST_DIR}/neuton-ai/neuton/lib/libneuton_arm_cortex-m4.a)
