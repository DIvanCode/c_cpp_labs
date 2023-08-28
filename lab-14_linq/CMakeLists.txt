cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-14_linq)

set(SOURCES_INCLUDE linq.hpp)

set(PROJECT_MAIN src/test.cpp)
set(PROJECT_MINIMAL_SMOKE_TEST tests/minimal_smoke_test.cpp)
set(PROJECT_SMOKE_TEST tests/smoke_test.cpp)

list(TRANSFORM SOURCES_INCLUDE PREPEND include/)

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES ${PROJECT_MAIN} ${SOURCES_INCLUDE})
set(MINIMAL_SMOKE_TEST_SOURCES ${PROJECT_MINIMAL_SMOKE_TEST} ${SOURCES_INCLUDE})
set(SMOKE_TEST_SOURCES ${PROJECT_SMOKE_TEST} ${SOURCES_INCLUDE})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)

add_executable(${X_PROJECT_NAME}-minimal_smoke_test ${MINIMAL_SMOKE_TEST_SOURCES})
target_include_directories(${X_PROJECT_NAME}-minimal_smoke_test PRIVATE include)

add_executable(${X_PROJECT_NAME}-smoke_test ${SMOKE_TEST_SOURCES})
target_include_directories(${X_PROJECT_NAME}-smoke_test PRIVATE include)