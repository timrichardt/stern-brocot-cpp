cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Force Clang++ as the compiler
set(CMAKE_CXX_COMPILER clang++)

# Add the source directory
include_directories(src)

# Define the executable
add_executable(main main.cpp src/tree.cpp src/homographic.cpp)
