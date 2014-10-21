cmake_minimum_required(VERSION 2.8.4)
project(Uebung2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
Transform.cpp
Transform.h
Test.h
Test.cpp
)
add_executable(Uebung2 ${SOURCE_FILES})