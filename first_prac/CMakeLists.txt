cmake_minimum_required(VERSION 3.16)
project(first_prac_formal)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(first_prac_formal main.cpp test.cpp LengthInLanguage.cpp LengthInLanguage.h)

target_link_directories(first_prac_formal PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(first_prac_formal PRIVATE GTest::GTest Threads::Threads)