#include <memory>
#include <iostream>
#include "Person.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test04 l-value reference with smart pointers

BOOST_AUTO_TEST_CASE( test04_lvalue_reference_with_smart_pointers ) {
    std::cout << "START testing reference for smart pointer - which is WRONG" << std::endl;

    long prev_refcnt;

    std::shared_ptr<Person> shared1 = std::make_shared<Person>();
    printf("shared1 reference count: %ld\n", shared1.use_count());

    // immutable_shared2: This is what I recommend for read-only (immutable) object
    prev_refcnt = shared1.use_count();
    std::shared_ptr<const Person> immutable_shared2 = shared1;
    std::cout << "For std::shared_ptr<const T> immutable_shared2,   immutable_shared2 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    printf("immutable_shared2 reference count: %ld\n", immutable_shared2.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // weak3
    prev_refcnt = shared1.use_count();
    std::weak_ptr<Person> weak3 = shared1;
    std::cout << "For std::weak_ptr<T>& weak3,   weak3 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is counted" << std::endl;
    else
        std::cout << "Reference is NOT counted" << std::endl;

    // immutable_weak4: Weak pointer for read-only (immutable) object
    prev_refcnt = shared1.use_count();
    std::weak_ptr<const Person> immutable_weak4 = shared1;
    std::cout << "For std::weak_ptr<T>& immutable_weak4,   immutable_weak4 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is counted" << std::endl;
    else
        std::cout << "Reference is NOT counted" << std::endl;

    // immutable_shared_from_weak5: if you do not use `const` keyword, compiler error message "No viable conversion from std::shared_ptr<const T> to std::shared_ptr<T>" appears
    std::shared_ptr<const Person> immutable_shared_from_weak5 = immutable_weak4.lock();
    std::cout << "For std::shared_ptr<const T>& immutable_shared_from_weak5,   immutable_shared_from_weak5 <-[lock()]- immutable_weak4 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is counted" << std::endl;
    else
        std::cout << "Reference is NOT counted" << std::endl;

    // wrong_immutable_shared6:
    //   (1) FATAL: `const` keyword may cause error related to memory deallocation, because `const` keyword prevents the pointer address from being nullptr
    //   (2) Even the object is mutable - Using `const` keyword does not work correctly
    prev_refcnt = shared1.use_count();
    const std::shared_ptr<Person> wrong_immutable_shared6 = shared1;
    std::cout << "For const std::shared_ptr<T>& wrong_immutable_shared6,   wrong_immutable_shared6 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // wrong_immutable_shared7: use_count will not increase due to reference (&)
    prev_refcnt = shared1.use_count();
    const std::shared_ptr<Person>& wrong_immutable_shared7 = shared1;
    std::cout << "For const std::shared_ptr<T>& wrong_immutable_shared7,   wrong_immutable_shared7 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // wrong_shared8: use_count will not increase due to reference (&)
    prev_refcnt = shared1.use_count();
    std::shared_ptr<Person>& wrong_shared8 = shared1;
    std::cout << "For std::shared_ptr<T>& wrong_shared8,   wrong_shared8 <- shared1" << std::endl;
    printf("shared1 reference count: %ld\n", shared1.use_count());
    if(prev_refcnt != shared1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    std::cout << "FINISHED testing reference for smart pointer" << std::endl;
}