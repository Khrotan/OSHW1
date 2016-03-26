cmake_minimum_required(VERSION 3.4)
project(OSHW1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -gdwarf-2")

set(SOURCE_FILES Process.cpp Process.h Pipe.cpp Pipe.h Pgraph.cpp Pgraph.h main.cpp )
add_executable(OSHW1 ${SOURCE_FILES})