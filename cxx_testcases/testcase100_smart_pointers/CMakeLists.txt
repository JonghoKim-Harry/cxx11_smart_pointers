cmake_minimum_required(VERSION 3.25.1)
project(cxx11_smart_pointers)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(testcase100_smart_pointers
    boost_test_main.cpp
    Person.h
    test101_allocate.cpp
    test102_refcount.cpp
    test103_reference.cpp
    test104_reference_for_smart_pointers.cpp
    test105_dangling_reference.cpp
    test106_unique_ptr_as_function_parameter.cpp
    test107_raw_pointer_pointing_to_unique_ptr.cpp
)

target_link_libraries(testcase100_smart_pointers
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
