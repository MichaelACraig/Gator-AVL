cmake_minimum_required(VERSION 3.26)
project(Project1DSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(test-unit)

add_executable(Project1DSA
        src/functions.cpp
        src/main.cpp
        src/Node.h
        test-unit/catch.hpp
        test-unit/test.cpp)
