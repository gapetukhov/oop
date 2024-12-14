cmake_minimum_required(VERSION 3.20)

project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)


include_directories(include)

set(SOURCES
    lab3/Rectangle.cpp
    lab3/Rhombus.cpp
    lab3/Trapeze.cpp
)

add_executable(tests main.cpp ${SOURCES})

target_link_libraries(tests gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
