cmake_minimum_required(VERSION 3.30)
project(lab_6)

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
    src/npc.cpp
    src/knight.cpp
    src/squirrel.cpp
    src/pegasus.cpp
    src/EntityFactory.cpp
    src/fileObserver.cpp
    src/conobs.cpp
    src/fightVisitor.cpp
)

add_executable(main_exe main.cpp ${SOURCES})

enable_testing()

add_executable(testtt test/tests.cpp ${SOURCES})
target_link_libraries(testtt gtest_main)

add_test(NAME lab6_test COMMAND testtt)