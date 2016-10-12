cmake_minimum_required(VERSION 3.6)
project(dataStructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES array2LinkedList/array2LinkedList.cpp)
add_executable(dataStructures ${SOURCE_FILES})