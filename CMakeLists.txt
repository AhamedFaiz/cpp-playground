cmake_minimum_required(VERSION 3.20)
project(cpp_playground CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Warnings catch many beginner bugs (e.g. signed/unsigned comparisons).
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
# AddressSanitizer + UBSan: out-of-bounds reads and undefined behaviour crash loudly in Debug.
add_compile_options($<$<CONFIG:Debug>:-fsanitize=address,undefined>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address,undefined>)

find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

# add_test_target(<name> <source>...) builds a GoogleTest executable and registers it with CTest.
function(add_test_target name)
  add_executable(${name} ${ARGN})
  target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${name} PRIVATE GTest::gtest_main)
  gtest_discover_tests(${name})
endfunction()

# Optional, untracked local targets.
include(${CMAKE_CURRENT_SOURCE_DIR}/local.cmake OPTIONAL)

add_test_target(first_unique_character_test problems/0387-first-unique-character/solution_test.cpp)
add_test_target(contains_duplicate_test problems/0217-contains-duplicate/solution_test.cpp)
add_test_target(valid_anagram_test problems/0242-valid-anagram/solution_test.cpp)
add_test_target(two_sum_test problems/0001-two-sum/solution_test.cpp)
