cmake_minimum_required (VERSION 3.15)

project (stl_reader)

add_library (stl_reader INTERFACE)
target_include_directories (stl_reader INTERFACE include)

option (STL_READER_BUILD_TESTS "Build the stl_reader tests." OFF)
if (STL_READER_BUILD_TESTS)
  add_subdirectory (tests)
endif ()
