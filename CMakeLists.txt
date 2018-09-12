# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.0)

# Project's name
project(movielist)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set C++11 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-DDEBUG -O2 -Wall -Wextra")

# Include files
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("/usr/local/Cellar/nlohmann_json/3.1.2/include")

# Source files
file(GLOB SOURCES "src/*.cpp")

add_executable(movielist ${SOURCES})
