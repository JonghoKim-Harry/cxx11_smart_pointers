#ifndef CPP_SMART_POINTERS_PERSON_H
#define CPP_SMART_POINTERS_PERSON_H

#include <string>
#include <memory>
#include <list>

class Person {
public:
    enum class Sex { UNASSIGNED, MALE, FEMALE };
    Person() = default;
    explicit Person(const std::string& name) : name_(name) { };

    ~Person() {
        std::cout << "Person deallocated!" << std::endl;
        printf("\tsex: %d\n\tbirth: %s\n\tname: %s\n\tnickname: %s\n", sex_, birth_.c_str(), name_.c_str(), nickname_ ==
                nullptr ? "" : nickname_->c_str());
    }

    // Members
    Sex sex_;
    const std::string birth_;
    std::string name_;
    //std::string& nickname_;   // References are not pointers
    std::unique_ptr<std::string> nickname_;
};

#endif //CPP_SMART_POINTERS_PERSON_H