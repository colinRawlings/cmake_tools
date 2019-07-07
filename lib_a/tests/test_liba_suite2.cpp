#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <a_lib.h>

BOOST_AUTO_TEST_SUITE(liba_suite)
BOOST_AUTO_TEST_SUITE(trivial_suite)

BOOST_AUTO_TEST_CASE(test_case3) { BOOST_TEST(true); }

BOOST_AUTO_TEST_CASE(test_case4) { BOOST_TEST(true); }

BOOST_AUTO_TEST_SUITE_END() // trivial_suite

BOOST_AUTO_TEST_SUITE(empty_suite)

BOOST_AUTO_TEST_SUITE_END() // empty

BOOST_AUTO_TEST_SUITE_END() // liba_suite
