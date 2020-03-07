find_package(Boost)

add_executable(main)

target_sources(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(USE_LIB_A)
  target_link_libraries(main lib_a)
endif(USE_LIB_A)

# hack to get h
target_link_libraries(main Boost::boost)

add_custom_command(TARGET main POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           $<TARGET_FILE_DIR:main> ${BINARY_OUTDIR}/$<CONFIG>)
