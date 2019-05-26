find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_runner)

target_sources(test_runner PRIVATE test_main.cpp test_suite1.cpp)

target_compile_definitions(test_runner PUBLIC BOOST_ALL_DYN_LINK)

target_link_libraries(test_runner Boost::unit_test_framework lib_a)

# target_link_libraries(test_runner ${Boost_LIBRARIES})
# target_include_directories(test_runner PRIVATE ${Boost_INCLUDE_DIRS})
