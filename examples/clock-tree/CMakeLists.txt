cmake_minimum_required(VERSION 3.0.0)
project(bmt-test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(clock-tree main.cpp)
