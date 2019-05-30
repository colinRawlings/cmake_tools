find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_library(test_liba)

target_sources(test_liba
               PRIVATE
               test_liba_main.cpp
               test_liba_suite1.cpp
               test_liba_suite2.cpp
               test_liba_dangerous.cpp)

target_compile_definitions(test_liba PUBLIC BOOST_ALL_DYN_LINK)

target_link_libraries(test_liba Boost::unit_test_framework lib_a)
