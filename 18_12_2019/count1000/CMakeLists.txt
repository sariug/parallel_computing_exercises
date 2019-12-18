cmake_minimum_required( VERSION 3.4.3 )

project( count1000 CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( count1000 count1000.cpp )

