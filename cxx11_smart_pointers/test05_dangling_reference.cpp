//
// Created by jongho on 23. 4. 24.
//
#include <memory>
#include <iostream>
#include "Person.h"

void test05_dangling_reference() {

    Person *raw1, *raw2;
    std::unique_ptr<Person> unique3;
    std::shared_ptr<Person> shared4, shared5;
    std::weak_ptr<Person> weak6;

    std::cout << "START testing dangling reference" << std::endl;

    raw1 = new Person();
    raw2 = new Person();
    unique3 = std::unique_ptr<Person>(new Person());
    shared4 = std::make_shared<Person>();
    shared5 = shared4;
    weak6 = shared4;

    const Person &ref1 = *raw1, &ref2 = *raw2;
    const Person &ref3 = *unique3;
    const Person &ref4 = *shared4, &ref5 = *shared5;
    std::cout << "You can not dereference weak6 because std::weak_ptr does not override dereference operator '*'" << std::endl;

    //
    // Initialize data
    //
    raw1->sex = Person::Sex::FEMALE;
    raw2->sex = Person::Sex::FEMALE;
    unique3->sex = Person::Sex::FEMALE;
    shared4->sex = Person::Sex::FEMALE;
    printf("Initialzie sex to: %d\n", Person::Sex::FEMALE);
    printf("ref1 sex: %d\n", ref1.sex);
    printf("ref2 sex: %d\n", ref2.sex);
    printf("ref3 sex: %d\n", ref3.sex);
    printf("ref4 sex: %d\n", ref4.sex);
    printf("ref5 sex: %d\n", ref5.sex);
    delete raw1, unique3, shared4, shared5;
    std::cout << "delete raw1, unique3, shared4, shared5" << std::endl;

    printf("(raw1 == nullptr): %s\n", (raw1 == nullptr) ? "true" : "false");   // WARN: raw1 can never be nullptr
    printf("(raw2 == nullptr): %s\n", (raw2 == nullptr) ? "true" : "false");   // WARN: raw2 will never be nullptr
    printf("(unique3 == nullptr): %s\n", (unique3 == nullptr) ? "true" : "false");
    printf("(shared4 == nullptr): %s\n", (shared4 == nullptr) ? "true" : "false");
    printf("(shared5 == nullptr): %s\n", (shared5 == nullptr) ? "true" : "false");
    std::cout << "You can not check (weak6 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    //
    // reset() will do:
    //   1. Deallocation
    //   2. Set pointer to nullptr
    //
    unique3.reset();
    shared4.reset();
    shared5.reset();
    weak6.reset();
    std::cout << "Reset unique3, shared4, shared5, weak6" << std::endl;

    printf("(raw1 == nullptr): %s\n", (raw1 == nullptr) ? "true" : "false");   // WARN: raw1 can never be nullptr
    printf("(raw2 == nullptr): %s\n", (raw2 == nullptr) ? "true" : "false");   // WARN: raw2 will never be nullptr
    printf("(unique3 == nullptr): %s\n", (unique3 == nullptr) ? "true" : "false");
    printf("(shared4 == nullptr): %s\n", (shared4 == nullptr) ? "true" : "false");
    printf("(shared5 == nullptr): %s\n", (shared5 == nullptr) ? "true" : "false");
    std::cout << "You can not check (weak6 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    std::cout << "FINISHED testing dangling reference" << std::endl;
}