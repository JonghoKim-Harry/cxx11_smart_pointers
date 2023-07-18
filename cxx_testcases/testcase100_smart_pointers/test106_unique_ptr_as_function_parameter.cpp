#include <memory>
#include <iostream>
#include "Person.h"

/**
 *   Recommended ways to use std::unique_ptr as a function parameter
 *      (1) By value
 *      (2) By const l-value reference
 *
 *   See: https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
 */
#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test06 std::unique_ptr as a function parameter

static void get_ownership_and_use_unique_ptr(std::unique_ptr<Person> var) {
    // Do nothing
}

static void borrow_and_use_unique_ptr(std::unique_ptr<Person> const &var) {
    // Do nothing
}

BOOST_AUTO_TEST_CASE( test06_unique_pointer_as_a_function_parameter ) {
    BOOST_TEST_MESSAGE("START TEST06 unique pointer as a function parameter");

    std::unique_ptr<Person> ptr(new Person);

    // COMPILATION ERROR - Call to deleted constructor of 'std::unique_ptr<Person>'
    // get_ownership_and_use_unique_ptr(ptr);

    // RUNTIME ERROR - memory access violation at address
    // get_ownership_and_use_unique_ptr(std::unique_ptr<Person>(new Person));

    // Get ownership and use unique pointer
    get_ownership_and_use_unique_ptr(std::move(ptr));

    // Borrow and use unique pointer
    borrow_and_use_unique_ptr(ptr);

    BOOST_TEST_MESSAGE("FINISHED TEST06 unique pointer as a function parameter");
}
