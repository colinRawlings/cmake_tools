

message(STATUS "Processing lib one")

set(lib_one_headers one_lib.h)
set(lib_one_source one_lib.cpp)

add_library(lib_one STATIC ${lib_one_headers} ${lib_one_source})

target_include_directories(lib_one INTERFACE ${lib_one_headers})