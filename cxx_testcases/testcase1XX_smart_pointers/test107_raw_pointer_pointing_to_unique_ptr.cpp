#include <memory>
#include "Person.h"
#include "Fixture.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test107 raw pointers pointing to std::unique_ptr

static void foo(const std::string& new_name, std::unique_ptr<Person> var);
static void bar(const std::string& new_name, std::unique_ptr<Person> *var);
static void boo(const std::string& new_name, std::unique_ptr<Person> &var);

BOOST_FIXTURE_TEST_SUITE( test107_raw_pointers_pointing_to_unique_pointers, Fixture )

BOOST_AUTO_TEST_CASE( test107_01_unique_pointer_as_a_parameter_using_std_move,
                      *boost::unit_test::expected_failures(1) ) {

    std::unique_ptr<Person> jongho(new Person(std::string("Jongho")));
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    //foo(std::string("foo"), jongho);   // COMPILATION ERROR: Call to deleted constructor of 'std::unique_ptr<Person>'
    foo(std::string("foo"), std::move(jongho));   // RUNTIME ERROR
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);
}

BOOST_AUTO_TEST_CASE( test107_02_raw_pointer_pointing_to_unique_pointer_as_a_parameter ) {

    std::unique_ptr<Person> jongho(new Person(std::string("Jongho")));
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    bar(std::string("bar"), &jongho);
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);
}

BOOST_AUTO_TEST_CASE( test107_03_lvalue_reference_pointing_to_unique_pointer_as_a_parameter ) {

    std::unique_ptr<Person> jongho(new Person(std::string("Jongho")));
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);

    boo(std::string("boo"), jongho);
    BOOST_TEST_MESSAGE("Name: " << jongho->name_);
}

BOOST_AUTO_TEST_SUITE_END()

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
