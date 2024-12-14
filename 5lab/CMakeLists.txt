cmake_minimum_required(VERSION 3.30)

project(DoublyLinkedListProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем Google Test с помощью FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(program main.cpp custom_memory_resources.h linked_list.h)

# Тесты
add_executable(tests test_linked_list.cpp custom_memory_resources.h linked_list.h)
target_link_libraries(tests gtest_main)
# Подключаем GoogleTest
include(GoogleTest)
gtest_discover_tests(tests)

