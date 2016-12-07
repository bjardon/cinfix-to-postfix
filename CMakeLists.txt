cmake_minimum_required(VERSION 3.5)
project(StackExpressionConverter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c util.h stack.h)
add_executable(StackExpressionConverter ${SOURCE_FILES})