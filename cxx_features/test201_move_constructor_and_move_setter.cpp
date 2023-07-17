#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE test201 move setters

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
    BOOST_TEST_MESSAGE("CALL CONSTRUCTOR: Bar::Bar()");
}

Bar::Bar(int i) : integer(i) {
    BOOST_TEST_MESSAGE("CALL CONSTRUCTOR: Bar::Bar(int i)");
}

Bar::~Bar() noexcept {
    BOOST_TEST_MESSAGE("CALL DESTRUCTOR: Bar::~Bar()");
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
    BOOST_TEST_MESSAGE("CALL CONSTRUCTOR: const T&");
}

Foo::Foo(Bar&& bar) noexcept {
    this->bar = std::move(bar);
    BOOST_TEST_MESSAGE("CALL CONSTRUCTOR: T&&");
}

void Foo::set(const Bar& bar) {
    this->bar = bar;
    BOOST_TEST_MESSAGE("CALL SETTER: const T&");
}

void Foo::set(Bar&& bar) noexcept {
    this->bar = std::move(bar);
    BOOST_TEST_MESSAGE("CALL SETTER: T&&");
}

void Foo::print() {
    BOOST_TEST_MESSAGE("my bar: " << this->bar.get());
}

BOOST_AUTO_TEST_CASE( test201_01_copy_constructor ) {
  Bar bar = Bar(1);
  Foo foo = Foo(bar);
  foo.print();

  Bar bar2 = Bar(11);
  foo.set(bar2);
  foo.print();
}

BOOST_AUTO_TEST_CASE( test201_02_move_constructor ) {
  Bar bar = Bar(2);
  Foo foo = Foo(std::move(bar));
  foo.print();

  Bar bar2 = Bar(22);
  foo.set(std::move(bar2));
  foo.print();
}
