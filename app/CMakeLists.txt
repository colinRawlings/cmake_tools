
add_executable(main)

target_sources(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(USE_LIB_A)
    target_link_libraries(main lib_a)
endif(USE_LIB_A)