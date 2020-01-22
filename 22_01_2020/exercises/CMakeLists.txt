cmake_minimum_required( VERSION 3.4.3 )

project( exercises CXX )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( exercises main.cpp )

# Linking matrix library 
target_link_libraries( exercises matrix )
MESSAGE(${CMAKE_CXX_FLAGS} )

IF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_custom_command( TARGET exercises POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:matrix>  $<TARGET_FILE_DIR:exercises> )
ENDIF() 
