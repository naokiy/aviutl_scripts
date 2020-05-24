cmake_minimum_required(VERSION 3.17)

project(shared)

file(GLOB_RECURSE MY_SOURCES "src/*.cc")

set(MY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE MY_HEADERS ${MY_INCLUDE_DIR}"/*.h")

add_library(${PROJECT_NAME}
    ${MY_SOURCES}
)

target_include_directories(${PROJECT_NAME}
   PUBLIC ${MY_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} cxx_x86)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${MY_HEADERS}"
)

add_subdirectory(test)