#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <a_lib.h>

BOOST_AUTO_TEST_SUITE(liba_suite)
BOOST_AUTO_TEST_SUITE(func_suite)

BOOST_AUTO_TEST_CASE(test_liba) { BOOST_CHECK_EQUAL(get_num_liba(), 42); }

BOOST_AUTO_TEST_SUITE_END() // func suite
BOOST_AUTO_TEST_SUITE_END() // liba_suite
