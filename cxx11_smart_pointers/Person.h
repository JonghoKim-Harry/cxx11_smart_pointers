#ifndef CPP_SMART_POINTERS_PERSON_H
#define CPP_SMART_POINTERS_PERSON_H

#include <string>
#include <memory>
#include <list>

class Person {
public:
    enum class Sex { UNASSIGNED, MALE, FEMALE };

    // Members
    Sex sex;
    const std::string birth;
    std::string name;
    //std::string& nickname;   // References are not pointers
    std::unique_ptr<std::string> nickname;
};

#endif //CPP_SMART_POINTERS_PERSON_H