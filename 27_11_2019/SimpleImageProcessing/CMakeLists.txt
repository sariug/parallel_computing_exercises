cmake_minimum_required( VERSION 3.4.3 )

project( SimpleImageProcessing CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( main main.cpp ppImageUtils.hpp ppImageUtils.cpp )

# Linking matrix library 
target_link_libraries( main matrix )

add_custom_command( TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/l.pgm ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command( TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/l.pgm  $<TARGET_FILE_DIR:main> )
