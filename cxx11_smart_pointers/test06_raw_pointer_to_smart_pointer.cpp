#include <memory>
#include <iostream>
#include "Person.h"

void test06_raw_pointer_pointing_to_smart_pointer() {
    std::cout << "START testing raw pointer pointing to for smart pointer" << std::endl;





    std::cout << "FINISHED testing raw pointer pointing to smart pointer" << std::endl;
}

static void foo(std::unique_ptr<Person> var) {

}

static void bar(std::unique_ptr<Person> *var) {

    var->reset();
    std::unique_ptr<Person> newvar(new Person());
}