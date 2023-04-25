//
// Created by jongho on 23. 4. 24.
//
#include <memory>
#include <iostream>
#include "Person.h"

void test04_reference_for_smart_pointer() {
    std::cout << "START testing reference for smart pointer - which is WRONG" << std::endl;

    long prev_refcnt;

    std::shared_ptr<Person> p1 = std::make_shared<Person>();
    printf("p1 reference count: %ld\n", p1.use_count());

    // p2: This is what I recommend for read-only (immutable) object
    prev_refcnt = p1.use_count();
    std::shared_ptr<const Person> p2 = p1;
    std::cout << "For std::shared_ptr<const T> p2,   p2 <- p1" << std::endl;
    printf("p1 reference count: %ld\n", p1.use_count());
    printf("p2 reference count: %ld\n", p2.use_count());
    if(prev_refcnt != p1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // p3: use_count will not increase due to reference (&)
    prev_refcnt = p1.use_count();
    const std::shared_ptr<Person>& p3 = p1;
    std::cout << "For const std::shared_ptr<T>& p3,   p3 <- p1" << std::endl;
    printf("p1 reference count: %ld\n", p1.use_count());
    printf("p2 reference count: %ld\n", p2.use_count());
    printf("p3 reference count: %ld\n", p3.use_count());
    if(prev_refcnt != p1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // p4: use_count will not increase due to reference (&)
    prev_refcnt = p1.use_count();
    std::shared_ptr<Person>& p4 = p1;
    std::cout << "For std::shared_ptr<T>& p4,   p4 <- p1" << std::endl;
    printf("p1 reference count: %ld\n", p1.use_count());
    printf("p2 reference count: %ld\n", p2.use_count());
    printf("p3 reference count: %ld\n", p3.use_count());
    printf("p4 reference count: %ld\n", p4.use_count());
    if(prev_refcnt != p1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;

    // p5: `const` keyword protects address, not object. The object is mutable
    prev_refcnt = p1.use_count();
    const std::shared_ptr<Person> p5 = p1;
    std::cout << "For const std::shared_ptr<T>& p5,   p5 <- p1" << std::endl;
    printf("p1 reference count: %ld\n", p1.use_count());
    printf("p2 reference count: %ld\n", p2.use_count());
    printf("p3 reference count: %ld\n", p3.use_count());
    printf("p4 reference count: %ld\n", p4.use_count());
    printf("p5 reference count: %ld\n", p5.use_count());
    if(prev_refcnt != p1.use_count())
        std::cout << "Reference is correctly counted" << std::endl;
    else
        std::cout << "FAIL: Reference is NOT counted" << std::endl;


    std::cout << "FINISHED testing reference for smart pointer" << std::endl;
}