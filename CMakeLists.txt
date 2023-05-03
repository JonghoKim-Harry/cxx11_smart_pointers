cmake_minimum_required(VERSION 3.25.1)
project(cxx11_smart_pointers)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(cxx11_smart_pointers
        cxx11_smart_pointers/cxx_pointers.h
        cxx11_smart_pointers/Person.h
        cxx11_smart_pointers/cxx_features.cpp
        cxx11_smart_pointers/test01_allocate.cpp
        cxx11_smart_pointers/test02_refcount.cpp
        cxx11_smart_pointers/test03_reference.cpp
        cxx11_smart_pointers/test04_reference_for_smart_pointers.cpp
        cxx11_smart_pointers/test05_dangling_reference.cpp
        cxx11_smart_pointers/test06_unique_ptr_as_function_parameter.cpp
        cxx11_smart_pointers/test07_raw_pointer_pointing_to_unique_ptr.cpp
)

target_link_libraries(cxx11_smart_pointers
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
