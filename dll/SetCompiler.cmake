# find_program(CMAKE_C_COMPILER "clang")
# find_program(CMAKE_CXX_COMPILER "clang++")

# find_program(CLANG_CXX_COMPILER "clang++")
# if(CLANG_CXX_COMPILER)
#     message("clang++ was found")
#     find_program(CMAKE_CXX_COMPILER "clang++")
#     set(CXX_COMPILE_OPTIONS
#         $<$<CONFIG:Release>:-O3 -flto -W4># Release
#         $<$<CONFIG:Debug>:-O0>            # Debug
#         $<$<CONFIG:RelWithDebgInfo>:-O3>  # RelWithDebInfo
#     )
# else()
#     set(CXX_COMPILE_OPTIONS
#         $<$<CONFIG:Release>:-O2 -flto -W4># Release
#         $<$<CONFIG:Debug>:-O0>            # Debug
#         $<$<CONFIG:RelWithDebgInfo>:-O2>  # RelWithDebInfo
#     )
# endif()

find_program(CLANG_C_COMPILER "clang")
find_program(CLANG_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "${CLANG_C_COMPILER}" CACHE string "clang compiler" FORCE)
set(CMAKE_CXX_COMPILER "${CLANG_CXX_COMPILER}" CACHE string "clang++ compiler" FORCE)