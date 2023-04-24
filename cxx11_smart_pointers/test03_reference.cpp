//
// Created by jongho on 23. 4. 24.
//
#include <memory>
#include <iostream>
#include "Person.h"

void test03_reference() {
    std::cout << "START testing reference" << std::endl;

    long prev_refcnt;

    std::shared_ptr<Person> p1 = std::make_shared<Person>();
    printf("p1 reference count: %ld\n", p1.use_count());

    // p2
    prev_refcnt = p1.use_count();
    const Person& p2 = *p1;
    std::cout << "const T& p2 <- *p1" << std::endl;
    printf("p1 reference count: %ld\n", p1.use_count());
    if(prev_refcnt +1 == p1.use_count())
        std::cout << "Reference is counted" << std::endl;
    else
        std::cout << "Reference is not counted" << std::endl;

    std::cout << "FINISHED testing reference" << std::endl;
}