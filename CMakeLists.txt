cmake_minimum_required(VERSION 3.10)

project(SternBrocotArithmetic)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Force Clang++ as the compiler
# set(CMAKE_CXX_COMPILER clang++)

add_compile_options(-Wall -Wextra -pedantic -g)

# Add the source directory
include_directories(src)

# Define the executable
# add_executable(main main.cpp src/tree.cpp src/homographic.cpp)
add_executable(main main.cpp src/tree.cpp src/homographic.cpp src/bihomographic.cpp src/arithmetic.cpp src/shanks.cpp src/tests.cpp)
