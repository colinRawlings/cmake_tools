cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 11)

#

option(USE_LIB_A "use lib a" OFF)
option(USE_LIB_C "use lib c" OFF)

#

message(STATUS "Configuring: ")
message(STATUS "USE_LIB_A: " ${USE_LIB_A})
message(STATUS "USE_LIB_C: " ${USE_LIB_C})

project(test_cmake_tools)

if(USE_LIB_A)
  add_subdirectory(lib_a)
endif(USE_LIB_A)

# add_subdirectory(lib_b)

if(USE_LIB_C)
  add_subdirectory(lib_c)
endif(USE_LIB_C)

#

add_subdirectory(app)
