cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)

#

project(test_cmake_tools)

# top level options

option(BUILD_SHARED_LIBS "build shared libs" ON)

option(USE_LIB_A "use lib a" ON)
option(USE_LIB_C "use lib c" OFF)

message(STATUS "Configuring: ")
message(STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS})
message(STATUS "USE_LIB_A: " ${USE_LIB_A})
message(STATUS "USE_LIB_C: " ${USE_LIB_C})

#

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# boost

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)

set(BOOST_DIR C:/third_party_libs/boost_1_70_0)
set(BOOST_INCLUDEDIR ${BOOST_DIR})
set(BOOST_LIBRARYDIR ${BOOST_DIR}/stage/lib)

#

if(USE_LIB_A)
  add_subdirectory(lib_a)
endif(USE_LIB_A)

# add_subdirectory(lib_b)

if(USE_LIB_C)
  add_subdirectory(lib_c)
endif(USE_LIB_C)

#

add_subdirectory(app)
