cmake_minimum_required( VERSION 3.4.3 )
project(parallel_computing)

OPTION ( PAR_COMP_TUTORIAL_ENABLE_PREVIOUS_WEEKS "Build previous weeks' solutions" OFF )
OPTION ( PAR_COMP_TUTORIAL_ENABLE_OMP "Enable OpenMP support" ON )


IF ( ${PAR_COMP_TUTORIAL_ENABLE_OMP} )
    add_definitions(-DPAR_COMP_OMP_ENABLED)
ENDIF()


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread -stdlib=libstdc++ -O3 -march=native ")
    IF ( ${PAR_COMP_TUTORIAL_ENABLE_OMP} )
        set (CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fopenmp ")
    ENDIF()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++17 -pthread  -O3 -march=native ")
    IF ( ${PAR_COMP_TUTORIAL_ENABLE_OMP} )
        set (CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fopenmp ")
    ENDIF()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
    IF ( ${PAR_COMP_TUTORIAL_ENABLE_OMP} )
        find_package(OpenMP)
        if (OPENMP_FOUND)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
        endif()
    ENDIF()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
   set (CMAKE_CXX_FLAGS "-std=c++17 -lpthread -O3 ")
endif()





include_directories(Matrix/inc)

add_subdirectory(Matrix)

IF ( ${PAR_COMP_TUTORIAL_ENABLE_PREVIOUS_WEEKS} )
    add_subdirectory(20_11_2019)
    add_subdirectory(27_11_2019)
    add_subdirectory(04_12_2019)
    add_subdirectory(11_12_2019)
    add_subdirectory(18_12_2019)
ENDIF()

add_subdirectory(15_01_2020)
add_subdirectory(22_01_2020)






