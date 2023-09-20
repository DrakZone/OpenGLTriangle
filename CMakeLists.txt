# Target CMake Version 3.14 And Above
cmake_minimum_required(VERSION 3.14)

project("OpenGLTriangle")

#Fetch Dependencies
include(FetchContent)

#GLFW - Platform Independent Windowing And Input
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_MakeAvailable(glfw)

add_executable("OpenGLTriangle" "src/main.cpp" "src/glad.c")
target_include_directories("OpenGLTriangle" PRIVATE "${CMAKE_SOURCE_DIR}/include/")
target_link_libraries("OpenGLTriangle" glfw)