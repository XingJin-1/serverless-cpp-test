cmake_minimum_required(VERSION 3.11)  # CMake version check

project(HELLO)               # Create project "hello"

set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

add_subdirectory(libhello)
add_subdirectory(src)
