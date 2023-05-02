#ifndef CPP_SMART_POINTERS_PERSON_H
#define CPP_SMART_POINTERS_PERSON_H

#include <string>
#include <memory>
#include <list>

class Person {
public:
    enum class Sex { UNASSIGNED, MALE, FEMALE };
    Person() = default;
    Person(const std::string& name) : name_(name) { };

    // Members
    Sex sex_;
    const std::string birth_;
    std::string name_;
    //std::string& nickname_;   // References are not pointers
    std::unique_ptr<std::string> nickname_;
};

#endif //CPP_SMART_POINTERS_PERSON_H