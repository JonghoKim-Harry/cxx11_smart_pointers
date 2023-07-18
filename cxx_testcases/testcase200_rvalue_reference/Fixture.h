#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>

struct Fixture {
    Fixture() { BOOST_TEST_MESSAGE("STARTING " << boost::unit_test::framework::current_test_case().p_name); }
    ~Fixture() { BOOST_TEST_MESSAGE("FINISHED " << boost::unit_test::framework::current_test_case().p_name); }
};
