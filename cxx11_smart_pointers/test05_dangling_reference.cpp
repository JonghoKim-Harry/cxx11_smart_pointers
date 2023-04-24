//
// Created by jongho on 23. 4. 24.
//
#include <memory>
#include <iostream>
#include "Person.h"

/**
 *   @pointer: store values, allocate, deallocate, reallocate
 *   @reference: references can not reseat - change address/reference they pointing to, dangling reference will return wrong value, reusable
 *   @smart_pointer: @pointer + reset() avoids dangling pointer by setting pointer to *nullptr*
 */
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

    if(raw1 == nullptr) printf("raw1 pointer: nullptr, values not available\n");
    else printf("raw1 pointer: available, sex: %d, %s\n", raw1->sex, (raw1->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN: raw1 can never be nullptr
    if(raw2 == nullptr) printf("raw2 pointer: nullptr, values not available\n");
    else printf("raw2 pointer: available, sex: %d, %s\n", raw2->sex, (raw2->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(unique3 == nullptr) printf("unique3 pointer: nullptr, values not available\n");
    else printf("unique3 pointer: available, sex: %d, %s\n", unique3->sex, (unique3->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared4 == nullptr) printf("shared4 pointer: nullptr, values not available\n");
    else printf("shared4 pointer: available, sex: %d, %s\n", shared4->sex, (shared4->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared5 == nullptr) printf("shared5 pointer: nullptr, values not available\n");
    else printf("shared5 pointer: available, sex: %d, %s\n", shared5->sex, (shared5->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    std::cout << "You can not check (weak6 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    //
    // reset() will do:
    //   1. Deallocation
    //   2. Set pointer to nullptr -> Runtime error rather than returning wrong value
    //
    unique3.reset();
    shared4.reset();
    shared5.reset();
    weak6.reset();
    std::cout << "Reset unique3, shared4, shared5, weak6" << std::endl;

    // pointers after reset
    if(raw1 == nullptr) printf("raw1 pointer: nullptr, values not available\n");
    else printf("raw1 pointer: available, sex: %d, %s\n", raw1->sex, (raw1->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN: raw1 can never be nullptr
    if(raw2 == nullptr) printf("raw2 pointer: nullptr, values not available\n");
    else printf("raw2 pointer: available, sex: %d, %s\n", raw2->sex, (raw2->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(unique3 == nullptr) printf("unique3 pointer: nullptr, values not available\n");
    else printf("unique3 pointer: available, sex: %d, %s\n", unique3->sex, (unique3->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared4 == nullptr) printf("shared4 pointer: nullptr, values not available\n");
    else printf("shared4 pointer: available, sex: %d, %s\n", shared4->sex, (shared4->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared5 == nullptr) printf("shared5 pointer: nullptr, values not available\n");
    else printf("shared5 pointer: available, sex: %d, %s\n", shared5->sex, (shared5->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    std::cout << "You can not check (weak6 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;

    // references after reset
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN: Invalid value
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    //
    // Reallocation of pointers
    //
    raw1 = new Person();
    unique3 = std::unique_ptr<Person>(new Person());
    shared4 = std::make_shared<Person>();

    raw1->sex = Person::Sex::MALE;
    unique3->sex = Person::Sex::MALE;
    shared4->sex = Person::Sex::MALE;

    // References can not reseat
    // ref1 = *raw1;
    // ref3 = *unique3;
    // ref4 = *shared4;

    //
    // Reuse of reference (without reseat)
    //
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");   // WARN: Invalid value
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");

    std::cout << "FINISHED testing dangling reference" << std::endl;
}