cmake_minimum_required( VERSION 3.4.3 )
project(Matrix)


set( MATRIX_CPP_FILES src/Matrix.cpp src/MatrixUtils.cpp )
set( MATRIX_HPP_FILES inc/Matrix.hpp inc/MatrixUtils.hpp )

include_directories( inc )

add_library( matrix SHARED ${MATRIX_CPP_FILES} ${MATRIX_HPP_FILES} )
