cmake_minimum_required(VERSION 3.8)
project(cs350_ass1_demo)

# Demos
add_executable(${PROJECT_NAME} demo_renderer.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC cs350_ass1)
