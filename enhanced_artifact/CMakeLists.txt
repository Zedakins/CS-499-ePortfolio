cmake_minimum_required(VERSION 3.16)
project(ExceptionsPortfolio CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Strict warnings
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

find_package(SQLite3 REQUIRED)

add_library(ep_core
    src/Exceptions.cpp
    src/Logger.cpp
    src/DB.cpp
    src/BatchProcessor.cpp
)

target_include_directories(ep_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(ep_core PUBLIC SQLite::SQLite3)

# Demo executable (optional)
add_executable(exceptions_demo src/Exceptions.cpp)
target_link_libraries(exceptions_demo PRIVATE ep_core)

# Tests (uses simple assertions; no external frameworks)
add_executable(ep_tests tests/test_exceptions.cpp)
target_link_libraries(ep_tests PRIVATE ep_core)

enable_testing()
add_test(NAME unit_tests COMMAND ep_tests)
