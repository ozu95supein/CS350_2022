cmake_minimum_required(VERSION 3.8)
project(cs350_ass1)

# Engine library
add_library(${PROJECT_NAME} 
    primitive.cpp primitive.hpp 
    camera.cpp camera.hpp 
    math.hpp math.cpp
    debug_system.cpp debug_system.hpp 
    shader.cpp shader.hpp 
    window.cpp window.hpp 
    opengl.cpp opengl.hpp
)
target_include_directories(${PROJECT_NAME} PUBLIC .)

# GLFW3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# GLAD
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

# Lodepng
find_package(lodepng CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC lodepng)