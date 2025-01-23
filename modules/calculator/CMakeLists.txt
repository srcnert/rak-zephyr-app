cmake_minimum_required(VERSION 3.20.0)
set(This calculator)

FILE(GLOB SOURCES *.cpp)

zephyr_library_named(${This})
zephyr_library_sources(${SOURCES})
zephyr_include_directories(.)