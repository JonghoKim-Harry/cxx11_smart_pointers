#include <memory>
#include "Person.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test07 raw pointers pointing to std::unique_ptr

static void foo(const std::string& new_name, std::unique_ptr<Person> var);
static void bar(const std::string& new_name, std::unique_ptr<Person> *var);
static void boo(const std::string& new_name, std::unique_ptr<Person> &var);

BOOST_AUTO_TEST_CASE( test07_raw_pointers_pointing_to_unique_pointers ) {
    BOOST_TEST_MESSAGE("START TEST07 raw pointers pointing to unique pointers");

    std::unique_ptr<Person> jongho(new Person(std::string("Jongho")));
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    // foo(std::string("foo"), jongho);   // COMPILATION ERROR: Call to deleted constructor of 'std::unique_ptr<Person>'
    //foo(std::string("foo"), std::move(jongho));   // RUNTIME ERROR

    bar(std::string("bar"), &jongho);
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    boo(std::string("boo"), jongho);
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    BOOST_TEST_MESSAGE("FINISHED TEST07 raw pointers pointing to unique pointers");
}

static void foo(const std::string& new_name, std::unique_ptr<Person> var) {

    var.reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    var = std::move(new_var);
    BOOST_TEST_MESSAGE("Run foo()");
}

static void bar(const std::string& new_name, std::unique_ptr<Person> *var) {

    var->reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    *var = std::move(new_var);

    BOOST_TEST_MESSAGE("Run bar()");
}

static void boo(const std::string& new_name, std::unique_ptr<Person> &var) {
    var.reset();
    std::unique_ptr<Person> new_var(new Person(new_name));
    var = std::move(new_var);

    BOOST_TEST_MESSAGE("Run boo()");
}