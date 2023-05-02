#include <memory>
#include <iostream>
#include "Person.h"

static void foo(const std::string& new_name, std::unique_ptr<Person> var);
static void bar(const std::string& new_name, std::unique_ptr<Person> *var);
static void boo(const std::string& new_name, std::unique_ptr<Person> &var);

void test07_raw_pointer_pointing_to_unique_ptr() {
    std::cout << "START testing raw pointer pointing to for smart pointer" << std::endl;

    std::unique_ptr<Person> jongho(new Person(std::string("Jongho")));
    std::cout << "Name: " << jongho->name_ << std::endl;

    // foo(std::string("foo"), jongho);   // COMPILATION ERROR: Call to deleted constructor of 'std::unique_ptr<Person>'
    //foo(std::string("foo"), std::move(jongho));   // RUNTIME ERROR
    //std::cout << "Name: " << jongho->name_ << std::endl;

    bar(std::string("bar"), &jongho);
    std::cout << "Name: " << jongho->name_ << std::endl;

    boo(std::string("boo"), jongho);
    std::cout << "Name: " << jongho->name_ << std::endl;

    std::cout << "FINISHED testing raw pointer pointing to smart pointer" << std::endl;
}

static void foo(const std::string& new_name, std::unique_ptr<Person> var) {

    var.reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    var = std::move(new_var);
    std::cout << "Run foo()" << std::endl;
}

static void bar(const std::string& new_name, std::unique_ptr<Person> *var) {

    var->reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    *var = std::move(new_var);

    std::cout << "Run bar()" << std::endl;
}

static void boo(const std::string& new_name, std::unique_ptr<Person> &var) {
    var.reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    var = std::move(new_var);

    std::cout << "Run boo()" << std::endl;
}