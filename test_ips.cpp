#define BOOST_TEST_MODULE test_ips

#include "test_stream.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ips)

BOOST_AUTO_TEST_CASE(test_stream)
{
    BOOST_CHECK(tsk_ip::get_hash() == 13285944928927920906u);
}

BOOST_AUTO_TEST_SUITE_END()