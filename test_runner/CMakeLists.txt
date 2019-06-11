find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_runner)

target_sources(test_runner PRIVATE test_main.cpp)

target_compile_definitions(test_runner PUBLIC BOOST_ALL_DYN_LINK)

target_link_libraries(test_runner Boost::unit_test_framework)
target_link_libraries(test_runner test_liba)

add_custom_command(TARGET test_runner POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           $<TARGET_FILE_DIR:test_runner> ${BINARY_OUTDIR})
