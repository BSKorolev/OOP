cmake_minimum_required(VERSION 3.20)
project(1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1
NumericalIntegration.hpp
TrapezoidalIntegration.hpp
SimpsonIntegration.hpp
SimpsonIntegration.cpp
TrapezoidalIntegration.cpp
main.cpp)