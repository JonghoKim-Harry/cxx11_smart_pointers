#include <memory>
#include "Person.h"

/**
 *   @pointer: store values, allocate, deallocate, reallocate
 *   @reference: references can not reseat - If reference changes object they pointing to,
 *               then dangling reference will return wrong value, reusable
 *   @smart_pointer: @pointer + reset() avoids dangling pointer by setting pointer to *nullptr*
 */

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test105 dangling l-value reference

#define PRINT_PTR(ptr)   do {                                                   \
    if((ptr) == nullptr) {                                                      \
        BOOST_TEST_MESSAGE(#ptr ": nullptr");                                   \
    }                                                                           \
    else {                                                                      \
        BOOST_TEST_MESSAGE(#ptr ": pointer available");                         \
        BOOST_TEST_MESSAGE(" - sex: " << (ptr)->sex_);                          \
        BOOST_TEST_MESSAGE(" - birth: " << (ptr)->birth_);                      \
        BOOST_TEST_MESSAGE(" - name: " << (ptr)->name_);                        \
    }                                                                           \
} while(false)


BOOST_AUTO_TEST_CASE( test105_dangling_lvalue_reference ) {
    BOOST_TEST_MESSAGE("START TEST105 dangling l-value references");

    Person *raw1, *raw2;
    std::unique_ptr<Person> unique3;
    std::shared_ptr<Person> shared4, shared5;
    std::weak_ptr<Person> weak6;
    std::shared_ptr<Person> shared_from_weak6;
    std::shared_ptr<Person> shared7;

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
    BOOST_TEST_MESSAGE("You can not dereference weak6 because std::weak_ptr does not override dereference operator '*'");

    //
    // Initialize data
    //
    raw1->sex_ = Person::Sex::FEMALE;
    raw2->sex_ = Person::Sex::FEMALE;
    unique3->sex_ = Person::Sex::FEMALE;
    shared4->sex_ = Person::Sex::FEMALE;
    shared7->sex_ = Person::Sex::FEMALE;
    BOOST_TEST_MESSAGE("Initialzie sex_ to: " << Person::Sex::FEMALE);
    BOOST_TEST_MESSAGE("ref1 sex_: " << ref1.sex_);
    BOOST_TEST_MESSAGE("ref2 sex_: " << ref2.sex_);
    BOOST_TEST_MESSAGE("ref3 sex_: " << ref3.sex_);
    BOOST_TEST_MESSAGE("ref4 sex_: " << ref4.sex_);
    BOOST_TEST_MESSAGE("ref5 sex_: " << ref5.sex_);
    BOOST_TEST_MESSAGE("ref6 sex_: " << ref6.sex_);
    BOOST_TEST_MESSAGE("ref7 sex_: " << ref7.sex_);
    BOOST_TEST_MESSAGE("ref8 sex_: " << ref8.sex_);

    delete raw1, unique3, shared4, shared5, weak6, shared_from_weak6, shared7, wrong_shared8;
    BOOST_TEST_MESSAGE("Delete a raw pointer: raw1");
    BOOST_TEST_MESSAGE("Delete smart pointers: unique3, shared4, shared5, weak6, shared_from_weak6, shared7, wrong_shared8");

    PRINT_PTR(raw1);
    PRINT_PTR(raw2);
    PRINT_PTR(unique3);
    PRINT_PTR(shared4);
    PRINT_PTR(shared5);
    PRINT_PTR(shared_from_weak6);
    PRINT_PTR(shared7);
    PRINT_PTR(wrong_shared8);
    BOOST_TEST_MESSAGE(boost::format("ref1 sex: %1%, %2%") % ref1.sex_ % (ref1.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref2 sex: %1%, %2%") % ref2.sex_ % (ref2.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref3 sex: %1%, %2%") % ref3.sex_ % (ref3.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref4 sex: %1%, %2%") % ref4.sex_ % (ref4.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref5 sex: %1%, %2%") % ref5.sex_ % (ref5.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref6 sex: %1%, %2%") % ref6.sex_ % (ref6.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref7 sex: %1%, %2%") % ref7.sex_ % (ref7.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref8 sex: %1%, %2%") % ref8.sex_ % (ref8.sex_ == Person::Sex::FEMALE ? "identical to FEMALE" : "data gone"));

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
    BOOST_TEST_MESSAGE("Reset smart pointers: unique3, shared4, shared5, weak6, shared7");
    BOOST_TEST_MESSAGE("We can not reset wrong_shared8 because `const` prevents the pointer from being modified (including set to nullptr)");

    // pointers after reset
    PRINT_PTR(raw1);
    PRINT_PTR(raw2);
    PRINT_PTR(unique3);
    PRINT_PTR(shared4);
    PRINT_PTR(shared5);
    PRINT_PTR(shared_from_weak6);
    PRINT_PTR(shared7);
    PRINT_PTR(wrong_shared8);

    // references after reset
    BOOST_TEST_MESSAGE(boost::format("ref1 sex_: %d, %s") % ref1.sex_ % ((ref1.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref2 sex_: %d, %s") % ref2.sex_ % ((ref2.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref3 sex_: %d, %s") % ref3.sex_ % ((ref3.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref4 sex_: %d, %s") % ref4.sex_ % ((ref4.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref5 sex_: %d, %s") % ref5.sex_ % ((ref5.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref6 sex_: %d, %s") % ref6.sex_ % ((ref6.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref7 sex_: %d, %s") % ref7.sex_ % ((ref7.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));
    BOOST_TEST_MESSAGE(boost::format("ref8 sex_: %d, %s") % ref8.sex_ % ((ref8.sex_ == Person::Sex::FEMALE) ? "identical to FEMALE" : "data gone"));

    //
    // Reallocation of pointers
    //
    raw1 = new Person();
    unique3 = std::unique_ptr<Person>(new Person());
    shared4 = std::make_shared<Person>();
    shared7 = std::make_shared<Person>();

    BOOST_TEST_MESSAGE("Second initialization. Initialize sex_ to: " << Person::Sex::MALE);
    raw1->sex_ = Person::Sex::MALE;
    unique3->sex_ = Person::Sex::MALE;
    shared4->sex_ = Person::Sex::MALE;
    shared7->sex_ = Person::Sex::MALE;

    // References can not reseat
    // ref1 = *raw1;
    // ref3 = *unique3;
    // ref4 = *shared4;
    // ref7 = *shared7;

    //
    // Reuse of reference (without reseat)
    //
    BOOST_TEST_MESSAGE(boost::format("ref1 sex_: %d, %s") % ref1.sex_ % ((ref1.sex_ == Person::Sex::MALE) ? "identical to MALE" : "data not available"));
    BOOST_TEST_MESSAGE(boost::format("ref3 sex_: %d, %s") % ref3.sex_ % ((ref3.sex_ == Person::Sex::MALE) ? "identical to MALE" : "data not available"));
    BOOST_TEST_MESSAGE(boost::format("ref4 sex_: %d, %s") % ref4.sex_ % ((ref4.sex_ == Person::Sex::MALE) ? "identical to MALE" : "data not available"));
    BOOST_TEST_MESSAGE(boost::format("ref5 sex_: %d, %s") % ref7.sex_ % ((ref7.sex_ == Person::Sex::MALE) ? "identical to MALE" : "data not available"));

    BOOST_TEST_MESSAGE("FINISHED TEST105 dangling l-value references");
}
