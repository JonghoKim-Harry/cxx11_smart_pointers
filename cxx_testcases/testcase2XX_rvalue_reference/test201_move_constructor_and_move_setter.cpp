#include "Fixture.h"

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test201 move constructors and move setters

//#include <utility>   // std::forward

class Bar {
public:
    Bar();
    Bar(int i);   // error: no matching function for call to ¡®Bar::Bar()¡¯
    ~Bar() noexcept;
    int get();

protected:
    int integer;
};

Bar::Bar() {
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL CONSTRUCTOR, this: " << this << ", bar: " << integer);
}

Bar::Bar(int i) : integer(i) {
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL CONSTRUCTOR, this: " << this << ", bar: " << integer);
}

Bar::~Bar() noexcept {
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL DESTRUCTOR, this: " << this << ", bar: " << integer);
}

int Bar::get() {
    return integer;
}

class Foo {
public:
    Foo(const Bar& bar);
    Foo(Bar&& bar) noexcept;

    //void set(Bar bar);
    //void set(const Bar bar);
    //void set(Bar& bar);
    void set(const Bar& bar);
    void set(Bar&& bar) noexcept;

    void print();

protected:
    Bar bar;
};

Foo::Foo(const Bar& bar) {
    this->bar = bar;
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL COPY CONSTRUCTOR, this: " << this);
}

Foo::Foo(Bar&& bar) noexcept {
    this->bar = std::move(bar);
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL MOVE CONSTRUCTOR, this: " << this);
}

void Foo::set(const Bar& bar) {
    this->bar = bar;
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL COPY SETTER, this: " << this);
}

void Foo::set(Bar&& bar) noexcept {
    this->bar = std::move(bar);
    BOOST_TEST_MESSAGE(typeid(this).name() << " CALL MOVE SETTER, this: " << this);
}

void Foo::print() {
    BOOST_TEST_MESSAGE("my bar: " << this->bar.get());
}

BOOST_FIXTURE_TEST_SUITE( test201, Fixture )

BOOST_AUTO_TEST_CASE( test201_01_copy_constructor_and_copy_setter ) {
  Bar bar = Bar(1);
  Foo foo = Foo(bar);
  foo.print();

  Bar bar2 = Bar(11);
  foo.set(bar2);
  foo.print();
}

BOOST_AUTO_TEST_CASE( test201_02_move_constructor_and_move_setter ) {
  Bar bar = Bar(2);
  Foo foo = Foo(std::move(bar));
  foo.print();

  Bar bar2 = Bar(22);
  foo.set(std::move(bar2));
  foo.print();
}

BOOST_AUTO_TEST_CASE( test201_03_copy_constructor_and_move_setter ) {
    Bar bar = Bar(3);
    Foo foo = Foo(bar);
    foo.print();

    Bar bar2 = Bar(33);
    foo.set(std::move(bar2));
    foo.print();
}

BOOST_AUTO_TEST_CASE( test201_04_move_constructor_and_copy_setter ) {
    Bar bar = Bar(4);
    Foo foo = Foo(std::move(bar));
    foo.print();

    Bar bar2 = Bar(44);
    foo.set(bar2);
    foo.print();
}

BOOST_AUTO_TEST_SUITE_END()
