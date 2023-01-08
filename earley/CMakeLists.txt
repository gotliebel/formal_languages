cmake_minimum_required(VERSION 3.24)
project(earley)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(earley main.cpp earley.cpp earley.h test.cpp)
target_link_directories(earley PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(earley PRIVATE GTest::GTest Threads::Threads)