# ===============================================================================
# The zlib/libpng License
#
# Copyright (c) 2023 Victor Matia <vmatir@gmail.com>
#
# This software is provided 'as-is', without any express or implied warranty. In
# no event will the authors be held liable for any damages arising from the use
# of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not claim
#    that you wrote the original software. If you use this software in a product,
#    an acknowledgment in the product documentation would be appreciated but is
#    not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# ===============================================================================

cmake_minimum_required(VERSION 3.24)
project(
  DO_SDL2_CPP
  VERSION 0.0.1.0
  DESCRIPTION "A Data-Oriented, modern C++ SDL2 wrapper."
  HOMEPAGE_URL "https://github.com/vitimiti/dosdl2cpp"
  LANGUAGES CXX)

option(${PROJECT_NAME}_BUILD_API_DOCS
       "Whether to configure and build the API docs" ${PROJECT_IS_TOP_LEVEL})

option(${PROJECT_NAME}_BUILD_EXAMPLES
       "Whether to configure and build the examples" ${PROJECT_IS_TOP_LEVEL})

if(NOT SDL2_FOUND)
  find_package(SDL2 REQUIRED)
endif()

include(GNUInstallDirs)

if(${PROJECT_IS_TOP_LEVEL})
  message(STATUS "Activating interface header verification")
  set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ON)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_sources(
  ${PROJECT_NAME}
  INTERFACE FILE_SET
            HEADERS
            FILES
            ${PROJECT_SOURCE_DIR}/include/dosdl2cpp/error.hpp
            # Include everything in one single header for PCH setups.
            ${PROJECT_SOURCE_DIR}/include/pch.hpp)

target_precompile_headers(
  ${PROJECT_NAME}
  INTERFACE
  <array>
  <cstddef>
  <cstdio>
  <string_view>
  <SDL.h>)

target_link_libraries(${PROJECT_NAME} INTERFACE ${SDL2_LIBRARIES})
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIRS}>
            ${SDL2_INCLUDE_DIRS})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
target_compile_options(
  ${PROJECT_NAME}
  INTERFACE
    # MSVC Flags
    #
    # Optimizations
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:/Zi>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:/O2>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:MinSizeRel>>:/Os>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RelWithDebInfo>>:/O2>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RelWithDebInfo>>:/Zi>
    # Level 4 warnings
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/W4>
    # 'identifier' : conversion from 'type1' to 'type2', possible loss of data
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14242>
    # 'operator' : conversion from 'type1' to 'type2', possible loss of data
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14254>
    # 'function' : member function does not override any base class virtual
    # member function
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14263>
    # 'class' : class has virtual functions, but destructor is not virtual
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14265>
    # 'operator' : unsigned/negative constant mismatch
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14287>
    # nonstandard extension used : 'var' : loop control variable declared in the
    # for-loop is used outside the for-loop scope
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/we4289>
    # 'operator' : expression is always false
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14296>
    # 'variable' : pointer truncation from 'type' to 'type'
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14311>
    # expression before comma evaluates to a function which is missing an
    # argument list
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14545>
    # function call before comma missing argument list
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14546>
    # 'operator' : operator before comma has no effect; expected operator with
    # side-effect
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14547>
    # 'operator' : operator before comma has no effect; did you intend
    # 'operator'?
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14549>
    # expression has no effect; expected expression with side-effect
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14555>
    # #pragma warning : there is no warning number 'number'
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14619>
    # 'instance' : construction of local static object is not thread-safe
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14640>
    # wide string literal cast to 'LPSTR'
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14905>
    # string literal cast to 'LPWSTR'
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14906>
    # illegal copy-initialization; more than one user-defined conversion has
    # been implicitly applied
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/w14928>
    # Specify standards conformance mode to the compiler. Use this option to
    # help you identify and fix conformance issues in your code, to make it both
    # more correct and more portable
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/permissive->
    # Make messages look prettier
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/diagnostics:column>
    # GNU / Clang Flags
    #
    # Optimizations
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-g3>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-Og>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-g0>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-O3>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:MinSizeRel>>:-g0>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:MinSizeRel>>:-Os>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RelWithDebInfo>>:-g2>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RelWithDebInfo>>:-O2>
    # "All" warnings
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wall>
    # Extra warnings
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wextra>
    # Warn about redundant semicolons after in-class function definitions
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wextra-semi>
    # Issue all the warnings demanded by strict ISO C and ISO C++; reject all
    # programs that use forbidden extensions, and some other programs that do
    # not follow ISO C and ISO C++
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wpedantic>
    # Warn whenever a local variable or type declaration shadows another
    # variable, parameter, type, class member
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wshadow>
    # Warn when a class has virtual functions and an accessible non-virtual
    # destructor itself or in an accessible polymorphic base class
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wnon-virtual-dtor>
    # Warn if an old-style (C-style) cast to a non-void type is used within a
    # C++ program
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wold-style-cast>
    # Warn whenever a pointer is cast such that the required alignment of the
    # target is increased
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wcast-align>
    # Warn about unused variables
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wunused>
    # Warn when a function declaration hides virtual functions from a base class
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Woverloaded-virtual>
    # Warn for implicit conversions that may alter a value
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wconversion>
    # Warn for implicit conversions that may change the sign of an integer
    # value, like assigning a signed integer expression to an unsigned integer
    # variable
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wsign-conversion>
    # Warn if the compiler detects paths that trigger erroneous or undefined
    # behavior due to dereferencing a null pointer
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wnull-dereference>
    # Give a warning when a value of type float is implicitly promoted to double
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wdouble-promotion>
    # Check calls to printf and scanf, etc., to make sure that the arguments
    # supplied have types appropriate to the format string specified, and that
    # the conversions specified in the format string make sense
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wformat=2>
    # Warn when a switch case falls through
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Wimplicit-fallthrough>
    # GNU Flags
    #
    # Warn when the indentation of the code does not reflect the block structure
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-Wmisleading-indentation>
    # Warn about duplicated conditions in an if-else-if chain
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-Wduplicated-cond>
    # Warn when an if-else has identical branches
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-Wduplicated-branches>
    # Warn about suspicious uses of logical operators in expressions
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-Wlogical-op>
    # Warn when an expression is cast to its own type
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-Wuseless-cast>
    # Make messages look prettier
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fdiagnostics-color=always>
    # Clang Flags
    #
    # Make messages look prettier
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<COMPILE_LANGUAGE:CXX>>:-fcolor-diagnostics>
)

if(${PROJECT_NAME}_BUILD_API_DOCS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/docs)
endif()

if(${PROJECT_NAME}_BUILD_EXAMPLES)
  add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
endif()
