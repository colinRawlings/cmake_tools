
message(STATUS "Processing lib two")

set(lib_two_headers two_lib.h)
set(lib_two_source two_lib.cpp)

add_library(lib_two STATIC ${lib_two_headers} ${lib_two_source})

target_include_directories(lib_two INTERFACE ${lib_two_headers})