cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(UNIT_TEST "Test${PROJECT_NAME}")

file(GLOB_RECURSE MY_TEST_SOURCES "*.cc")

add_executable(
    ${UNIT_TEST}
    ${MY_TEST_SOURCES}
)

find_package(GTest REQUIRED)

target_link_libraries(${UNIT_TEST} 
    GTest::GTest GTest::Main
    ${LOGIC_LIB_STATIC}
    shared cxx_x86
)

set_target_properties(${UNIT_TEST} PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

gtest_discover_tests(${UNIT_TEST})