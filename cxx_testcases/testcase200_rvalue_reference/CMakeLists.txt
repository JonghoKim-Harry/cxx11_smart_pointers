cmake_minimum_required(VERSION 3.25.1)
project(cxx11_smart_pointers)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(cxx_features_run
    boost_test_main.cpp
    test201_move_constructor_and_move_setter.cpp
)

target_link_libraries(cxx_features_run
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
