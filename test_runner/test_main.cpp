#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

bool init_unit_test()
{
    framework::master_test_suite().p_name.value = "Test runner test";

    return true;
}