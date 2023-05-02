cmake_minimum_required(VERSION 3.26)
project(cxx11_smart_pointers)

set(CMAKE_CXX_STANDARD 11)

add_executable(cxx11_smart_pointers
        cxx11_smart_pointers/cxx_pointers.h
        cxx11_smart_pointers/Person.h
        cxx11_smart_pointers/cxx_features.cpp
        cxx11_smart_pointers/test01_allocate.cpp
        cxx11_smart_pointers/test02_refcount.cpp
        cxx11_smart_pointers/test04_reference_for_smart_pointers.cpp
        cxx11_smart_pointers/test03_reference.cpp
        cxx11_smart_pointers/test05_dangling_reference.cpp
        cxx11_smart_pointers/test06_raw_pointer_pointing_to_smart_pointer.cpp
)