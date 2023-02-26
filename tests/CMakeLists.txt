cmake_minimum_required (VERSION 3.15)
project(stl_reader_tests)

add_executable (
    stl_reader_tests
    read_stl.t.cpp
    remove_doubles.t.cpp
    utils.cpp)

include (FetchContent)
FetchContent_Declare (
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1
    GIT_SHALLOW ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable (googletest)

target_link_libraries (stl_reader_tests gtest_main)
add_custom_target (copyResources ALL COMMAND cmake -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data data)
