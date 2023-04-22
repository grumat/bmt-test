cmake_minimum_required(VERSION 3.0.0)

include(CTest)
enable_testing()

add_executable(clock-tree ${STARTUP_FILE} main.cpp)

