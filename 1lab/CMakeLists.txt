cmake_minimum_required(VERSION 3.30)

project(max_multiple_project)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(qu main.cpp max_multiple.cpp)

enable_testing()
add_executable(tests tests.cpp max_multiple.cpp)
target_link_libraries(tests gtest_main)

add_test(NAME CountOnesTests COMMAND tests)