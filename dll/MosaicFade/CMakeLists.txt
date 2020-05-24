cmake_minimum_required(VERSION 3.17)

project(MosaicFade)

set(TARGET_INTERFACE "${PROJECT_NAME}Interface")

file(GLOB_RECURSE MY_SOURCES "src/*")
add_library(${TARGET_INTERFACE} INTERFACE)
set_target_properties(${TARGET_INTERFACE} PROPERTIES
    INTERFACE_SOURCES "${MY_SOURCES}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(LOGIC_LIB "${PROJECT_NAME}Logic")
add_library(${LOGIC_LIB} STATIC)
target_include_directories(${LOGIC_LIB}
    PUBLIC ${MY_INCLUDE_DIR}
)
target_link_libraries(${LOGIC_LIB}
    PUBLIC ${TARGET_INTERFACE}
    PRIVATE shared cxx_x86
)

set(LOGIC_LIB_STATIC "${LOGIC_LIB}Static")
add_library(${LOGIC_LIB_STATIC} STATIC)
target_link_libraries(${LOGIC_LIB_STATIC}
    PUBLIC ${TARGET_INTERFACE}
    PRIVATE shared cxx_x86)
set_target_properties(${LOGIC_LIB_STATIC} PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

file(GLOB_RECURSE MY_DLL_SOURCES "lua_adapter/*")
add_library(${PROJECT_NAME} MODULE ${MY_DLL_SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE with_lua ${LOGIC_LIB} shared cxx_x86
)

add_subdirectory(test)