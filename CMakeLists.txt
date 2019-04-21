cmake_minimum_required(VERSION 3.12)

#

option(USE_LIB_A "use lib a" OFF)
option(USE_LIB_C "use lib c" OFF)

#

project(test_cmake_tools)

#add_subdirectory(lib_b)

if(USE_LIB_C)
    add_subdirectory(lib_c)
endif(USE_LIB_C)

#

add_subdirectory(app)
