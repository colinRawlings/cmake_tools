
project(LibA)

message(STATUS "Processing lib_a")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib_a STATIC)

target_sources(lib_a PRIVATE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/a_lib.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/a_lib.h)

target_include_directories(lib_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)