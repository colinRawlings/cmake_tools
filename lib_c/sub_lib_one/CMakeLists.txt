

message(STATUS "Processing lib one")

set(lib_one_headers one_lib.h)
set(lib_one_source one_lib.cpp)

add_library(lib_one STATIC)

target_sources(lib_one PRIVATE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/one_lib.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/one_lib.h)

target_include_directories(lib_one PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)