# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

target_sources(app PRIVATE src/main.c)
if(CONFIG_USE_SEGGER_RTT AND CONFIG_BOARD_RAK11720)
  target_sources(app PRIVATE src/rtt.c)
endif()
