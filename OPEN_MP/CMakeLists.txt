cmake_minimum_required( VERSION 3.4.3 )
project(OPEN_MP)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "-std=c++11 -pthread -stdlib=libstdc++ -O0 ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++11 -pthread  -O0 ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
   set (CMAKE_CXX_FLAGS "-std=c++11 -lpthread -O0 ")
endif()

add_subdirectory(open_mp)
