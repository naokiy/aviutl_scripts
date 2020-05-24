cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(UNIT_TEST TestShared)

file(GLOB_RECURSE MY_TEST_SOURCES "*.cc")

add_executable(
    ${UNIT_TEST}
    ${MY_TEST_SOURCES}
    ${MY_SOURCES}
)

find_package(GTest REQUIRED)

target_link_libraries(${UNIT_TEST} GTest::GTest GTest::Main cxx_x86)

target_include_directories(${UNIT_TEST}
   PRIVATE ${MY_INCLUDE_DIR}
)

set_property(TARGET ${UNIT_TEST}
    PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

gtest_discover_tests(${UNIT_TEST})