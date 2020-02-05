cmake_minimum_required( VERSION 3.4.3 )
project(Matrix)


set( MATRIX_CPP_FILES src/Matrix.cpp src/MatrixUtils.cpp )
set( MATRIX_HPP_FILES inc/Matrix.hpp inc/MatrixUtils.hpp )
set( MATRIX_TEST_CPP_FILES tests/tests.cpp )

include_directories( inc )
include_directories( catch )

add_library( matrix SHARED ${MATRIX_CPP_FILES} ${MATRIX_HPP_FILES} )
add_executable( matrix_testrunner ${MATRIX_TEST_CPP_FILES} ${MATRIX_HPP_FILES} )

target_link_libraries( matrix_testrunner matrix)

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_custom_command( TARGET matrix_testrunner POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:matrix>  $<TARGET_FILE_DIR:matrix_testrunner> )
ENDIF() 
