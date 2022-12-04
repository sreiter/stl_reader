project(stl_reader)
cmake_minimum_required(VERSION 3.16)

# add the stl_reader as a single target:
add_library(stl_reader INTERFACE)

target_include_directories(stl_reader
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

install(DIRECTORY include/stl_reader DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# define the export of our cmake target:
install(
  TARGETS stl_reader
  EXPORT stl_readerTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  EXPORT stl_readerTargets
  FILE stl_readerTargets.cmake
  NAMESPACE stl_reader::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stl_reader
)

# include some helper macros for generating cmake config files:
include(CMakePackageConfigHelpers)

# create the cmake config files:
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/stl_readerConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stl_reader
)

# install the configuration files that we using the helper macros above:
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/stl_readerConfig.cmake" # cmake config file
  "${CMAKE_CURRENT_BINARY_DIR}/stl_readerConfigVersion.cmake" # cmake version file
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stl_reader
)

set(version 1.0.0)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/stl_readerConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion # probably don't want to set this. Would need to check other options.
)