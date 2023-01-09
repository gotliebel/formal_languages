cmake_minimum_required(VERSION 3.16)
project(cocke-younger-kasami)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(cocke-younger-kasami convert_to_chomsky.h convert_to_chomsky.cpp main.cpp cyk.h cyk.cpp test.cpp)

target_link_directories(cocke-younger-kasami PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(cocke-younger-kasami PRIVATE GTest::GTest Threads::Threads)