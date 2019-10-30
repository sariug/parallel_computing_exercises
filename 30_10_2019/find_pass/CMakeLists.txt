cmake_minimum_required( VERSION 3.4.3 )

project( firstproject CXX )
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
find_package( Threads )
add_executable( find_pass main.cpp )
target_link_libraries (find_pass  ${CMAKE_THREAD_LIBS_INIT})

