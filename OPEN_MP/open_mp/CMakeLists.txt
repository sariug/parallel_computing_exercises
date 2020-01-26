cmake_minimum_required( VERSION 3.4.3 )

project( open_mp CXX )
find_package(OpenMP REQUIRED)
add_executable( main tasks.cpp )
target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)
