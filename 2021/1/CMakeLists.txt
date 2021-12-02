cmake_minimum_required(VERSION 3.21)
project(1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) # Builds with input.txt file readable (https://stackoverflow.com/a/38166227)

add_executable(1 main.cpp)
