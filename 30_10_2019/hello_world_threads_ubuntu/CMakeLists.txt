cmake_minimum_required( VERSION 3.4.3 )

project( firstproject CXX )
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
find_package( Threads )
add_executable( firstproject main.cpp )
target_link_libraries (firstproject  ${CMAKE_THREAD_LIBS_INIT})

