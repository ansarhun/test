cmake_minimum_required(VERSION 3.3)
project(Testing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
include_directories(SYSTEM ${Qt5Core_INCLUDE_DIRS})
message(${Qt5Core_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH {CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(gtest)
include(CodeCoverage)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)