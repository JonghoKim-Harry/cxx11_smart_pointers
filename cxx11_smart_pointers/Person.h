#ifndef CPP_SMART_POINTERS_PERSON_H
#define CPP_SMART_POINTERS_PERSON_H

#include <string>
#include <memory>
#include <list>
#include <boost/test/unit_test.hpp>
#include <boost/format.hpp>

class Person {
public:
    Person() = default;
    explicit Person(const std::string& name) : name_(name) { };

    typedef enum { UNASSIGNED, MALE, FEMALE } Sex;

    inline const char * tostring(const Sex& sex) {
        switch (sex) {
            case Person::MALE:
                return "MALE";
            case Person::FEMALE:
                return "FEMALE";

        }
    };

    ~Person() {
        BOOST_TEST_MESSAGE("Person deallocated!");
        BOOST_TEST_MESSAGE("\t- sex: " << sex_);
        BOOST_TEST_MESSAGE("\t- birth: " << birth_);
        BOOST_TEST_MESSAGE("\t- name: " << name_);
        BOOST_TEST_MESSAGE("\t- nickname: " << (nickname_ == nullptr ? "" : *nickname_));
        BOOST_TEST_MESSAGE("\t- email: " << (email_ == nullptr ? "" : *email_));
    }

    // Members
    Sex sex_;
    const std::string birth_;
    std::string name_;
    //std::string& nickname_;   // References are not pointers
    std::unique_ptr<std::string> nickname_;
    std::string *email_;
};

#endif //CPP_SMART_POINTERS_PERSON_H