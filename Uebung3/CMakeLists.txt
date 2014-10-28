cmake_minimum_required(VERSION 2.8.4)
project(Uebung3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
LZW-Codierer.cpp
Text.txt
Test.txt)
add_executable(Uebung3 ${SOURCE_FILES})