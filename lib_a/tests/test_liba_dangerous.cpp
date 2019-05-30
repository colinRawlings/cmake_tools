#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <a_lib.h>

BOOST_AUTO_TEST_SUITE(liba_suite)
BOOST_AUTO_TEST_SUITE(dangerous_suite)

BOOST_AUTO_TEST_CASE(test_derefence) { BOOST_REQUIRE(dereference_null()); }

BOOST_AUTO_TEST_CASE(test_never_return) { BOOST_REQUIRE(never_return()); }

BOOST_AUTO_TEST_CASE(test_throw_an_exception)
{
    BOOST_REQUIRE(throw_an_exception());
}

BOOST_AUTO_TEST_SUITE_END() // dangerous suite
BOOST_AUTO_TEST_SUITE_END() // liba_suite