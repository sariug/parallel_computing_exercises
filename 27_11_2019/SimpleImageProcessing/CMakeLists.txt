cmake_minimum_required( VERSION 3.4.3 )

project( SimpleImageProcessing CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(matrix SHARED  Matrix.cpp MatrixUtils.cpp Matrix.hpp MatrixUtils.hpp ppImageUtils.hpp ppImageUtils.cpp)

add_executable( main main.cpp  )
target_link_libraries(main matrix)

add_custom_command( TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/l.pgm ${CMAKE_CURRENT_BINARY_DIR} )