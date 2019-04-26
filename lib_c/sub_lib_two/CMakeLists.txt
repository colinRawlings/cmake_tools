message(STATUS "Processing lib two")

set(lib_two_headers two_lib.h)
set(lib_two_source two_lib.cpp)

add_library(lib_two STATIC)

target_sources(lib_two PRIVATE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/two_lib.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/two_lib.h)

target_include_directories(lib_two PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)