cmake_minimum_required( VERSION 3.4.3 )
project(third_week)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread -stdlib=libstdc++ -O3 ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread  -O3 ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
   set (CMAKE_CXX_FLAGS "-std=c++17 -lpthread -O3 ")
endif()


add_subdirectory(1D_convection)
