cmake_minimum_required( VERSION 3.4.3 )

project( Matrix CXX )

add_executable( main main.cpp Matrix.cpp MatrixUtils.cpp Matrix.hpp MatrixUtils.hpp
ppImageUtils.hpp ppImageUtils.cpp)