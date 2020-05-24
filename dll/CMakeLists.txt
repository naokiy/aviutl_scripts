cmake_minimum_required(VERSION 3.17)

project(AviUtlScripts CXX)

enable_testing()

find_package(Lua51 REQUIRED)

add_library(cxx_x86 INTERFACE)
set(CXX_X86_COMPILE_OPTIONS
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:-O2 -W4>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:-O0>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebgInfo>>:-O2>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -Werror -flto>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-O0>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:RelWithDebgInfo>>:-O3>
    $<$<CXX_COMPILER_ID:Clang>:-m32>
)
set(CXX_X86_COMPILE_FEATURES "cxx_std_17")
set(CXX_X86_LINK_OPTIONS
    $<$<CXX_COMPILER_ID:Clang>:-m32>
)
set_target_properties(cxx_x86 PROPERTIES
    INTERFACE_COMPILE_OPTIONS "${CXX_X86_COMPILE_OPTIONS}"
    INTERFACE_COMPILE_FEATURES "${CXX_X86_COMPILE_FEATURES}"
    INTERFACE_LINK_OPTIONS "${CXX_X86_LINK_OPTIONS}"
)

add_library(with_lua INTERFACE)
set_target_properties(with_lua PROPERTIES
    INTERFACE_LINK_LIBRARIES "${LUA_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
)

add_subdirectory(Shared)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDubInfo)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel)

add_subdirectory(ErrorDiffusionDither)
add_subdirectory(MosaicFade)