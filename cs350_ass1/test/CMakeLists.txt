cmake_minimum_required(VERSION 3.8)
project(cs350_ass1_test)

############################
# Testing
add_executable(${PROJECT_NAME} common.hpp debug_draw.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC cs350_ass1) # Link against the engine

# GTest
find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest GTest::gtest_main) # Link against GTest



