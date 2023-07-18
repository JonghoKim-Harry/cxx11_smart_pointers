#include <memory>
#include "Person.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test102 reference count for std::shared_ptr and std::weak_ptr

BOOST_AUTO_TEST_CASE( test102_reference_count_for_shared_pointer_and_weak_pointer ) {
    BOOST_TEST_MESSAGE("START TEST102 reference count for shared pointers and weak pointers");

    std::shared_ptr<Person> shared1, shared2, shared3;
    std::weak_ptr<Person> weak4;

    // Allocation
    shared1 = std::make_shared<Person>();
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());

    // Assignment
    shared2 = shared1;
    BOOST_TEST_MESSAGE("shared2 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 reference count: " << shared2.use_count());

    // Assignment again
    shared3 = shared2;
    BOOST_TEST_MESSAGE("shared3 <- shared2");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 reference count: " << shared2.use_count());
    BOOST_TEST_MESSAGE("shared3 reference count: " << shared3.use_count());

    /**
     *   Test how weak pointer affects reference count
     */
    // Before test
    BOOST_TEST_MESSAGE("shared1 reference count before weak pointer: " << shared1.use_count());

    // Assignment
    weak4 = shared1;
    BOOST_TEST_MESSAGE("weak4 <- shared1");
    BOOST_TEST_MESSAGE("shared1 reference count after weak pointer: " << shared1.use_count());

    BOOST_TEST_MESSAGE("shared1 type: " << typeid(shared1).name() << ", reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 type: " << typeid(shared2).name() << ", reference count: " << shared2.use_count());
    BOOST_TEST_MESSAGE("shared3 type: " << typeid(shared3).name() << ", reference count: " << shared3.use_count());
    BOOST_TEST_MESSAGE("  weak4 type: " << typeid(weak4).name()   << ", reference count: " << weak4.use_count());

    // Reset shared1
    shared1.reset();
    BOOST_TEST_MESSAGE("Reset shared1");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 reference count: " << shared2.use_count());
    BOOST_TEST_MESSAGE("shared3 reference count: " << shared3.use_count());
    BOOST_TEST_MESSAGE("weak4   reference count: " << weak4.use_count());
    BOOST_TEST_MESSAGE("shared1" << ((shared1 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared2" << ((shared2 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared3" << ((shared3 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='");

    // Reset shared2
    shared2.reset();
    BOOST_TEST_MESSAGE("Reset shared2");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 reference count: " << shared2.use_count());
    BOOST_TEST_MESSAGE("shared3 reference count: " << shared3.use_count());
    BOOST_TEST_MESSAGE("weak4   reference count: " << weak4.use_count());
    BOOST_TEST_MESSAGE("shared1" << ((shared1 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared2" << ((shared2 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared3" << ((shared3 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='");

    // Reset shared3
    shared3.reset();
    BOOST_TEST_MESSAGE("Reset shared3");
    BOOST_TEST_MESSAGE("shared1 reference count: " << shared1.use_count());
    BOOST_TEST_MESSAGE("shared2 reference count: " << shared2.use_count());
    BOOST_TEST_MESSAGE("shared3 reference count: " << shared3.use_count());
    BOOST_TEST_MESSAGE("weak4   reference count: " << weak4.use_count());
    BOOST_TEST_MESSAGE("shared1" << ((shared1 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared2" << ((shared2 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("shared3" << ((shared3 == nullptr) ? ": nullptr" : " has data"));
    BOOST_TEST_MESSAGE("You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='");

    BOOST_TEST_MESSAGE("FINISHED TEST102 reference count for shared pointers and weak pointers");
}
