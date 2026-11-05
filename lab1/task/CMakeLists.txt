cmake_minimum_required(VERSION 3.15)

project(task CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE debug)

add_executable(out 
               main.cpp
               include/singlyLinkedList
               )

target_include_directories(out PRIVATE include)

