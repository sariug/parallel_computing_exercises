cmake_minimum_required( VERSION 3.4.3 )

project( dining_philosophers CXX )
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread  -O3 -march=native ")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( dining_philosophers dining_philosophers.cpp )


