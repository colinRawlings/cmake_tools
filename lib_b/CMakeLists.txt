set(lib_b_headers b_lib.h)
set(lib_b_source b_lib.cpp)

add_library(lib_b STATIC ${lib_b_headers} ${lib_b_source})

target_include_directories(lib_b INTERFACE ${lib_b_headers})