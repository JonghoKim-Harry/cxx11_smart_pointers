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

static void foo(std::unique_ptr<Person> var) {
    // Do nothing
}

static void bar(std::unique_ptr<Person> const &var) {
    // Do nothing
}

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test06 std::unique_ptr as a function parameter

BOOST_AUTO_TEST_CASE( test06_unique_pointer_as_a_function_parameter ) {
    std::cout << "START testing to use std::unique_ptr as a function parameter" << std::endl;

    std::unique_ptr<Person> ptr(new Person);

    // foo(ptr);   // COMPILATION ERROR: Call to deleted constructor of 'std::unique_ptr<Person>'
    foo(std::unique_ptr<Person>(new Person));   // By value
    foo(std::move(ptr));   // By value
    bar(ptr);   // By const l-value reference

    std::cout << "FINISHED testing to use std::unique_ptr as a function parameter" << std::endl;
}