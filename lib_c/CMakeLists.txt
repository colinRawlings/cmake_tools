
project(LibB)

message(STATUS "Processing lib_b")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

# options

set(LIB_ONE_NAME one)
set(LIB_TWO_NAME two)

set(c_sub_lib_name "one" CACHE STRING "sub lib used by lib c")
set_property(CACHE c_sub_lib_name
             PROPERTY STRINGS ${LIB_ONE_NAME} ${LIB_TWO_NAME})

#

add_library(lib_c)

target_sources(lib_c PRIVATE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/c_lib.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/c_lib.h)

target_include_directories(lib_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# select sub lib

message(STATUS "Selecting sub lib, lib name: " ${c_sub_lib_name})

if(${c_sub_lib_name} STREQUAL ${LIB_ONE_NAME})
    message(STATUS "Using lib one")
    add_subdirectory(sub_lib_one)
elseif(${c_sub_lib_name} STREQUAL ${LIB_TWO_NAME})
    message(STATUS "Using lib two")
    add_subdirectory(sub_lib_two)
else()
    message(STATUS "No lib found")
endif(${c_sub_lib_name} STREQUAL ${LIB_ONE_NAME})