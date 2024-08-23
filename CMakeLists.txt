# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(UnzipProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories using relative path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/miniz)

# Add executable
add_executable(unzip unzip.cpp miniz/miniz.c)

# Link against the precompiled miniz library
target_link_libraries(unzip miniz)