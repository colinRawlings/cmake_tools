
project(LibB)

message(STATUS "Processing: lib_b")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib_b)

target_sources(lib_b PRIVATE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/b_lib.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/b_lib.h)

target_include_directories(lib_b PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)