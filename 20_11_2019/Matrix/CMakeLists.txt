cmake_minimum_required( VERSION 3.4.3 )

project( Matrix CXX )

add_executable( matrix_driver main.cpp Matrix.cpp MatrixUtils.cpp Matrix.hpp MatrixUtils.hpp )

