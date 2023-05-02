#include <iostream>
#include "cxx_pointers.h"

int main() {
    test01_allocate();
    test02_refcount();
    test03_reference();
    test04_reference_for_smart_pointer();
    test05_dangling_reference();
    test06_unique_ptr_as_function_parameter();

    return 0;
}