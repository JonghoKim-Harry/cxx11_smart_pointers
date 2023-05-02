#include <iostream>
#include "cxx_pointers.h"

int main() {
    test01_allocate();
    test02_refcount();
    test03_reference();
    test04_reference_for_smart_pointer();
    test05_dangling_reference();
    test06_raw_pointer_pointing_to_smart_pointer();

    return 0;
}