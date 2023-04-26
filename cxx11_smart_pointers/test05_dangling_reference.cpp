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
    std::shared_ptr<Person> shared_from_weak6;
    std::shared_ptr<Person> shared7;

    std::cout << "START testing dangling reference" << std::endl;

    raw1 = new Person();
    raw2 = new Person();
    unique3 = std::unique_ptr<Person>(new Person());
    shared4 = std::make_shared<Person>();
    shared5 = shared4;
    weak6 = shared4;
    shared_from_weak6 = weak6.lock();
    shared7 = std::make_shared<Person>();
    const std::shared_ptr<Person> wrong_shared8 = shared7;

    const Person &ref1 = *raw1, &ref2 = *raw2;
    const Person &ref3 = *unique3;
    const Person &ref4 = *shared4, &ref5 = *shared5, &ref6 = *shared_from_weak6, &ref7 = *shared7, &ref8 = *wrong_shared8;
    std::cout << "You can not dereference weak6 because std::weak_ptr does not override dereference operator '*'" << std::endl;

    //
    // Initialize data
    //
    raw1->sex = Person::Sex::FEMALE;
    raw2->sex = Person::Sex::FEMALE;
    unique3->sex = Person::Sex::FEMALE;
    shared4->sex = Person::Sex::FEMALE;
    shared7->sex = Person::Sex::FEMALE;
    printf("Initialzie sex to: %d\n", Person::Sex::FEMALE);
    printf("ref1 sex: %d\n", ref1.sex);
    printf("ref2 sex: %d\n", ref2.sex);
    printf("ref3 sex: %d\n", ref3.sex);
    printf("ref4 sex: %d\n", ref4.sex);
    printf("ref5 sex: %d\n", ref5.sex);
    printf("ref6 sex: %d\n", ref6.sex);
    printf("ref7 sex: %d\n", ref7.sex);
    printf("ref8 sex: %d\n", ref8.sex);

    delete raw1, unique3, shared4, shared5, weak6, shared_from_weak6, shared7, wrong_shared8;
    std::cout << "Delete a raw pointer: raw1" << std::endl << "Delete smart pointers: unique3, shared4, shared5, weak6, shared_from_weak6, shared7, wrong_shared8" << std::endl;

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
    if(shared_from_weak6 == nullptr) printf("shared_from_weak6 pointer: nullptr, values not available\n");
    else printf("shared_from_weak6 pointer: available, sex: %d, %s\n", shared_from_weak6->sex, (shared_from_weak6->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared7 == nullptr) printf("shared7 pointer: nullptr, values not available\n");
    else printf("shared7 pointer: available, sex: %d, %s\n", shared7->sex, (shared7->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(wrong_shared8 == nullptr) printf("wrong_shared8 pointer: nullptr, values not available\n");
    else printf("wrong_shared8 pointer: available, sex: %d, %s\n", wrong_shared8->sex, (wrong_shared8->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref6 sex: %d, %s\n", ref6.sex, (ref6.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref7 sex: %d, %s\n", ref7.sex, (ref7.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref6 sex: %d, %s\n", ref8.sex, (ref8.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    //
    // reset() will do:
    //   1. Deallocation
    //   2. Set pointer to nullptr -> Runtime error rather than returning wrong value
    //
    unique3.reset();
    shared4.reset();
    shared5.reset();
    weak6.reset();
    shared7.reset();
    // wrong_shared8.reset();   // compilation error: You can not reset because reset() modifies pointer to nullptr but the pointer is `const`
    std::cout << "Reset smart pointers: unique3, shared4, shared5, weak6, shared7" << std::endl;
    std::cout << "We can not reset wrong_shared8 because `const` prevents the pointer from being modified (including set to nullptr)" << std::endl;

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
    if(shared_from_weak6 == nullptr) printf("shared_from_weak6 pointer: nullptr, values not available\n");
    else printf("shared_from_weak6 pointer: available, sex: %d, %s\n", shared_from_weak6->sex, (shared_from_weak6->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(shared7 == nullptr) printf("shared7 pointer: nullptr, values not available\n");
    else printf("shared7 pointer: available, sex: %d, %s\n", shared7->sex, (shared7->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    if(wrong_shared8 == nullptr) printf("wrong_shared8 pointer: nullptr, values not available\n");
    else printf("wrong_shared8 pointer: available, sex: %d, %s\n", wrong_shared8->sex, (wrong_shared8->sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    std::cout << "You can not check (weak6 == nullptr) because std::weak_ptr does not override operator '=='" << std::endl;

    // references after reset
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref2 sex: %d, %s\n", ref2.sex, (ref2.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");   // WARN: Invalid value
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref5 sex: %d, %s\n", ref5.sex, (ref5.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref6 sex: %d, %s\n", ref6.sex, (ref6.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref7 sex: %d, %s\n", ref7.sex, (ref7.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");
    printf("ref8 sex: %d, %s\n", ref8.sex, (ref8.sex == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone");

    //
    // Reallocation of pointers
    //
    raw1 = new Person();
    unique3 = std::unique_ptr<Person>(new Person());
    shared4 = std::make_shared<Person>();
    shared7 = std::make_shared<Person>();

    printf("Second initialization. Initialize sex to: %d\n", Person::Sex::MALE);
    raw1->sex = Person::Sex::MALE;
    unique3->sex = Person::Sex::MALE;
    shared4->sex = Person::Sex::MALE;
    shared7->sex = Person::Sex::MALE;

    // References can not reseat
    // ref1 = *raw1;
    // ref3 = *unique3;
    // ref4 = *shared4;
    // ref7 = *shared7;

    //
    // Reuse of reference (without reseat)
    //
    printf("ref1 sex: %d, %s\n", ref1.sex, (ref1.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");
    printf("ref3 sex: %d, %s\n", ref3.sex, (ref3.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");   // WARN: Invalid value
    printf("ref4 sex: %d, %s\n", ref4.sex, (ref4.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");
    printf("ref7 sex: %d, %s\n", ref7.sex, (ref7.sex == Person::Sex::MALE) ? "identical to MALE" : "data not available");

    std::cout << "FINISHED testing dangling reference" << std::endl;
}