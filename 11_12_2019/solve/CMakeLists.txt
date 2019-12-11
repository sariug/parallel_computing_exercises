cmake_minimum_required( VERSION 3.4.3 )

project( solve CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( solve solve.cpp )

# Linking matrix library 
target_link_libraries( solve matrix )

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_custom_command( TARGET solve POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:matrix>  $<TARGET_FILE_DIR:solve> )
ENDIF() 
