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

message(STATUS "Configuring Doxygen to generate the API documentation")
find_package(Doxygen REQUIRED dot)

set(DOXYGEN_PROJECT_NAME "Data-Oriented SDL2 C++ Wrapper")
set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
set(DOXYGEN_PROJECT_BRIEF ${PROJECT_DESCRIPTION})
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_CREATE_SUBDIRS YES)
set(DOXYGEN_FILE_PATTERNS *.hpp)
set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_GENERATE_RTF YES)
set(DOXYGEN_GENERATE_MAN YES)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_GENERATE_DOCBOOK YES)
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_ENABLE_PREPROCESSING NO)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")

doxygen_add_docs(
  ${PROJECT_NAME}_API_DOCS "${PROJECT_SOURCE_DIR}/README.md"
  "${PROJECT_SOURCE_DIR}/include" ALL
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Generate doxygen documentation")
