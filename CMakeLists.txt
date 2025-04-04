cmake_minimum_required(VERSION 3.10)
project(CarSaleManagementSystem C)

# Set C standard and compiler flags
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Output binary
add_executable(main ${SOURCES})

