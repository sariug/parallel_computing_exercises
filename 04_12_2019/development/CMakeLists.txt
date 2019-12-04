cmake_minimum_required( VERSION 3.4.3 )

project( development CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( development main.cpp )

# Linking matrix library 
target_link_libraries( development matrix )

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_custom_command( TARGET development POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:matrix>  $<TARGET_FILE_DIR:development> )
ENDIF() 
