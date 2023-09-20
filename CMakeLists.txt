# Target CMake Version 3.14 And Above
cmake_minimum_required(VERSION 3.14)

project("OpenGLTriangle")

add_executable("OpenGLTriangle" "src/main.cpp" "src/glad.c")
target_include_directories("OpenGLTriangle" PRIVATE "${CMAKE_SOURCE_DIR}/include/")