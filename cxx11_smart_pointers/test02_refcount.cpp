#include <memory>
#include <iostream>
#include "Person.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test02 reference count for std::shared_ptr and std::weak_ptr

BOOST_AUTO_TEST_CASE( test02_reference_count_for_shared_pointer_and_weak_pointer ) {

    std::shared_ptr<Person> shared1, shared2, shared3;
    std::weak_ptr<Person> weak4;

    std::cout << "START testing reference counting" << std::endl;
    shared1 = std::make_shared<Person>();

    printf("shared1 reference count: %ld\n", shared1.use_count());

    shared2 = shared1;
    std::cout << "shared2 <- shared1" << std::endl;

    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("shared2 reference count: %ld\n", shared2.use_count());

    shared3 = shared2;

    std::cout << "shared3 <- shared2" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("shared2 reference count: %ld\n", shared2.use_count());
    printf("shared3 reference count: %ld\n", shared3.use_count());

    //
    // Test how weak pointer affects reference count
    //
    printf("shared1 reference count before weak pointer: %ld\n", shared1.use_count());
    weak4 = shared1;
    printf("shared1 reference count after weak pointer: %ld\n", shared1.use_count());

    printf("shared1 type: %s, reference count: %ld\n", typeid(shared1).name(), shared1.use_count());
    printf("shared2 type: %s, reference count: %ld\n", typeid(shared2).name(), shared2.use_count());
    printf("shared2 type: %s, reference count: %ld\n", typeid(shared3).name(), shared3.use_count());
    printf("shared2 type: %s, reference count: %ld\n", typeid(weak4).name(), weak4.use_count());

    //
    // Reset shared1
    //
    shared1.reset();
    std::cout << "Reset shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("shared2 reference count: %ld\n", shared2.use_count());
    printf("shared3 reference count: %ld\n", shared3.use_count());
    printf("weak4 reference count: %ld\n", weak4.use_count());
    printf("(shared1 == nullptr): %s\n", (shared1 == nullptr) ? "true" : "false");
    printf("(shared2 == nullptr): %s\n", (shared2 == nullptr) ? "true" : "false");
    printf("(shared3 == nullptr): %s\n", (shared3 == nullptr) ? "true" : "false");
    std::cout << "You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;

    //
    // Reset shared2
    //
    shared2.reset();
    std::cout << "Reset shared2" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("shared2 reference count: %ld\n", shared2.use_count());
    printf("shared3 reference count: %ld\n", shared3.use_count());
    printf("weak4 reference count: %ld\n", weak4.use_count());
    printf("(shared1 == nullptr): %s\n", (shared1 == nullptr) ? "true" : "false");
    printf("(shared2 == nullptr): %s\n", (shared2 == nullptr) ? "true" : "false");
    printf("(shared3 == nullptr): %s\n", (shared3 == nullptr) ? "true" : "false");
    std::cout << "You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;

    //
    // Reset shared3
    //
    shared3.reset();
    std::cout << "Reset shared3" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("shared2 reference count: %ld\n", shared2.use_count());
    printf("shared3 reference count: %ld\n", shared3.use_count());
    printf("weak4 reference count: %ld\n", weak4.use_count());
    printf("(shared1 == nullptr): %s\n", (shared1 == nullptr) ? "true" : "false");
    printf("(shared2 == nullptr): %s\n", (shared2 == nullptr) ? "true" : "false");
    printf("(shared3 == nullptr): %s\n", (shared3 == nullptr) ? "true" : "false");
    std::cout << "You can not check (weak4 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;

    std::cout << "FINISHED testing reference counting" << std::endl;
}