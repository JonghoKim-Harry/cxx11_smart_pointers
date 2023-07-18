#include <memory>
#include "Person.h"
#include "Fixture.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test104 l-value reference with smart pointers

BOOST_FIXTURE_TEST_CASE( test104_lvalue_reference_with_smart_pointers, Fixture ) {

    long prev_refcnt;

    std::shared_ptr<Person> shared1 = std::make_shared<Person>();
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());

    // immutable_shared2: This is what I recommend for read-only (immutable) object
    prev_refcnt = shared1.use_count();
    std::shared_ptr<const Person> immutable_shared2 = shared1;
    BOOST_TEST_MESSAGE("For std::shared_ptr<const T> immutable_shared2,   immutable_shared2 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("immutable_shared2 reference count: " << immutable_shared2.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is correctly counted");
    else
        BOOST_TEST_MESSAGE("FAIL: Reference is NOT counted");

    // weak3
    prev_refcnt = shared1.use_count();
    std::weak_ptr<Person> weak3 = shared1;
    BOOST_TEST_MESSAGE("For std::weak_ptr<T>& weak3,   weak3 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is correctly counted");
    else
        BOOST_TEST_MESSAGE("FAIL: Reference is NOT counted");

    // immutable_weak4: Weak pointer for read-only (immutable) object
    prev_refcnt = shared1.use_count();
    std::weak_ptr<const Person> immutable_weak4 = shared1;
    BOOST_TEST_MESSAGE("For std::weak_ptr<T>& immutable_weak4,   immutable_weak4 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is counted");
    else
        BOOST_TEST_MESSAGE("Reference is NOT counted");

    // immutable_shared_from_weak5: if you do not use `const` keyword, compiler error message "No viable conversion from std::shared_ptr<const T> to std::shared_ptr<T>" appears
    std::shared_ptr<const Person> immutable_shared_from_weak5 = immutable_weak4.lock();
    BOOST_TEST_MESSAGE("For std::shared_ptr<const T>& immutable_shared_from_weak5,   immutable_shared_from_weak5 <-[lock()]- immutable_weak4 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is counted");
    else
        BOOST_TEST_MESSAGE("Reference is NOT counted");

    // wrong_immutable_shared6:
    //   (1) FATAL: `const` keyword may cause error related to memory deallocation, because `const` keyword prevents the pointer address from being nullptr
    //   (2) Even the object is mutable - Using `const` keyword does not work correctly
    prev_refcnt = shared1.use_count();
    const std::shared_ptr<Person> wrong_immutable_shared6 = shared1;
    BOOST_TEST_MESSAGE("For const std::shared_ptr<T>& wrong_immutable_shared6,   wrong_immutable_shared6 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is correctly counted");
    else
        BOOST_TEST_MESSAGE("FAIL: Reference is NOT counted");

    // wrong_immutable_shared7: use_count will not increase due to reference (&)
    prev_refcnt = shared1.use_count();
    const std::shared_ptr<Person>& wrong_immutable_shared7 = shared1;
    BOOST_TEST_MESSAGE("For const std::shared_ptr<T>& wrong_immutable_shared7,   wrong_immutable_shared7 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is correctly counted");
    else
        BOOST_TEST_MESSAGE("FAIL: Reference is NOT counted");

    // wrong_shared8: use_count will not increase due to reference (&)
    prev_refcnt = shared1.use_count();
    std::shared_ptr<Person>& wrong_shared8 = shared1;
    BOOST_TEST_MESSAGE("For std::shared_ptr<T>& wrong_shared8,   wrong_shared8 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        BOOST_TEST_MESSAGE("Reference is correctly counted");
    else
        BOOST_TEST_MESSAGE("FAIL: Reference is NOT counted");
}
