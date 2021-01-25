cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -std=c++14")

project(mkSchedule)

add_executable(
    mkSchedule
    main.cpp
    consoleOutputs.h
    consoleOutputs.cpp
)

