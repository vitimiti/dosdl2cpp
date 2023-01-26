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

message(STATUS "Configuring example 001 - Hello, SDL")

add_executable(HELLO_SDL)
target_sources(HELLO_SDL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_precompile_headers(HELLO_SDL PRIVATE
                          ${PROJECT_SOURCE_DIR}/include/dosdl2cpp/pch.hpp)

target_link_libraries(HELLO_SDL PRIVATE ${PROJECT_NAME})

if(WIN32)
  set_target_properties(HELLO_SDL PROPERTIES OUTPUT_NAME HelloSdl)
else()
  set_target_properties(HELLO_SDL PROPERTIES OUTPUT_NAME hello-sdl)
endif()

target_compile_options(
  HELLO_SDL
  PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/WX>
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<COMPILE_LANGUAGE:CXX>>:-Werror>
)
