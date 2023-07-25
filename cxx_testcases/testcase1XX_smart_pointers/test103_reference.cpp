#include <memory>
#include "Person.h"
#include "Fixture.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test103 l-value reference with smart pointers

BOOST_FIXTURE_TEST_CASE( test103_lvalue_reference, Fixture ) {

    long prev_refcnt;

    std::shared_ptr<Person> p1 = std::make_shared<Person>();
    BOOST_TEST_MESSAGE("p1 reference count: " << p1.use_count());

    // p2
    prev_refcnt = p1.use_count();
    const Person& p2 = *p1;

    BOOST_TEST_MESSAGE("const T& p2 <- *p1");
    BOOST_TEST_MESSAGE("p1 reference count: " << p1.use_count());
    if(prev_refcnt +1 == p1.use_count())
        BOOST_TEST_MESSAGE("Reference is counted");
    else
        BOOST_TEST_MESSAGE("Reference is not counted");
}
