cmake_minimum_required( VERSION 3.4.3 )
project(parallel_computing)


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread -stdlib=libstdc++ -O3 -march=native ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread  -O3 -march=native ")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
   set (CMAKE_CXX_FLAGS "-std=c++17 -lpthread -O3 ")
endif()
OPTION ( PAR_COMP_TUTORIAL_ENABLE_PREVIOUS_WEEKS "Build previous weeks' solutions" OFF )


include_directories(Matrix/inc)

add_subdirectory(Matrix)

IF ( ${PAR_COMP_TUTORIAL_ENABLE_PREVIOUS_WEEKS} )
    add_subdirectory(30_10_2019)
    add_subdirectory(06_11_2019)
    add_subdirectory(13_11_2019)
    add_subdirectory(20_11_2019)
    add_subdirectory(27_11_2019)
ENDIF()

add_subdirectory(04_12_2019)
add_subdirectory(11_12_2019)






