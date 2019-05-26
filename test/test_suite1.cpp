#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <a_lib.h>

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_case1) { BOOST_TEST_WARN(sizeof(int) < 4U); }

BOOST_AUTO_TEST_CASE(test_case2)
{
    BOOST_TEST_REQUIRE(1 == 2);
    BOOST_FAIL("Should never reach this line");
}

BOOST_AUTO_TEST_CASE(test_liba) { BOOST_CHECK_EQUAL(get_num_liba(), 42); }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(test_suite2)

BOOST_AUTO_TEST_CASE(test_case3) { BOOST_TEST(true); }

BOOST_AUTO_TEST_CASE(test_case4) { BOOST_TEST(false); }

BOOST_AUTO_TEST_SUITE_END()