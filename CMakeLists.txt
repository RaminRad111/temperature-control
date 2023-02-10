cmake_minimum_required(VERSION 3.10)

project(TempControl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(TempControl temp_control.cpp)
target_link_libraries(TempControl ${GTEST_BOTH_LIBRARIES})

enable_testing()
add_test(TempControl TempControl)

