# Chapter3- example illustrating how to create a shared library
# Additionally the example shows how to set a postfix for debug libraries and 
# how to handle symbol visibilities for shared libraries
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.17)

project(
    Greeter
    VERSION 1.0.0
    DESCRIPTION
        "A simple C++ project to demonstrate creating executables and libraries in CMake"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# set the postfix "d" for the resulting .so or .dll files when building the
# library in debug mode
set(CMAKE_DEBUG_POSTFIX
    d
)

# add the library target
add_library(Greeter)

# set properties for the target. VERSION set the library version to the project
# version * SOVERSION set the compatibility  version for the library to the
# major number of the version
set_target_properties(
    Greeter
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

# add sources to the library target
target_sources(
    Greeter
    PRIVATE src/hello.cpp src/internal.cpp
)

# define the C++ standard needed to compile this library and make it visible to
# dependers
target_compile_features(
    Greeter
    PUBLIC cxx_std_17
)

# set the include directories
target_include_directories(
    Greeter
    PRIVATE src/Greeter
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# if using limited visibility, set CXX_VISIBILILTY_PRESET to "hidden"
include(GenerateExportHeader)
set_property(
    TARGET Greeter
    PROPERTY CXX_VISIBILITY_PRESET "hidden"
)
# Hide inlined functions by default, reducing the size of the library
set_property(
    TARGET Greeter
    PROPERTY VISIBILITY_INLINES_HIDDEN TRUE
)
# this command generates a header file in the CMAKE_CURRENT_BINARY_DIR which
# sets the visibility attributes according to the compiler settings
generate_export_header(
    Greeter
    EXPORT_FILE_NAME
    export/hello/export_hello.hpp
)
# Add CMAKE_CURRENT_BINARY_DIR to the include path so the generated header can
# be found
target_include_directories(
    Greeter
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    
)

# include the GNUInstallDirs module to get the canonical install paths defined
include(GNUInstallDirs)

# Install the library and export the CMake targets
install(
    TARGETS Greeter
    EXPORT GreeterTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# install the public headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install the generated export header
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/export/hello/export_hello.hpp"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hello
)

# configure the CMake package file so the libray can be included with find_package() later
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "GreeterConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/GreeterConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GreeterConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/Greeter
)

# install the CMake targets
install(
    EXPORT GreeterTargets
    FILE GreeterTargets.cmake
    NAMESPACE Greeter::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/Greeter
)