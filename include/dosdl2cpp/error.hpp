//==============================================================================
// The zlib/libpng License
//
// Copyright (c) 2023 Victor Matia <vmatir@gmail.com>
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not claim
//    that you wrote the original software. If you use this software in a
//    product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//==============================================================================

#ifndef DO_SDL2_CPP_ERROR_HPP
#define DO_SDL2_CPP_ERROR_HPP

#include <array>
#include <cstddef>
#include <cstdio>
#include <string_view>

#include <SDL.h>

namespace dosdl2cpp::error {
template <typename... Args>
auto set(std::string_view const& fmt, Args... args) -> std::int32_t {
  return SDL_SetError(fmt.data(), args...);
}

auto get() -> std::string_view { return {SDL_GetError()}; }

#if SDL_VERSION_ATLEAST(2, 0, 14)
template <std::size_t BufferSize>
auto get_msg(std::array<char, BufferSize>& buffer)
    -> std::array<char, BufferSize> {
  auto* c_buffer = buffer.data();
  auto* c_buffer_out =
      SDL_GetErrorMsg(c_buffer, static_cast<std::int32_t>(BufferSize));

  std::array<char, BufferSize> buffer_out{};
  for (std::size_t i = 0; i < BufferSize; i++) {
    buffer[i]     = c_buffer[i];
    buffer_out[i] = c_buffer_out[i];
  }

  return buffer_out;
}
#endif // SDLv >= 2.0.14

auto clear() -> void { SDL_ClearError(); }
} // namespace dosdl2cpp::error

#endif // DO_SDL2_CPP_ERROR_HPP

/// @file error.hpp
/// @brief The SDL2 error functions.

/// @fn auto dosdl2cpp::error::set(std::string_view const& fmt,Args... args) ->
/// std::int32_t
/// @brief Set the error message.
/// @tparam Args Variadic arguments to format the message.
/// @param fmt The std::string_view to format and set the error with.
/// @param args A variadic argument list to format the message.
/// @remarks This function always returns -1.
/// @sa dosdl2cpp::error::get()
/// @sa dosdl2cpp::error::clear()
///
/// Set an error message with the given std::string_view as a formattable
/// string, which will use the variadic arguments to format itself.
///
/// The std::string_view must be formatted in a way that it is compatible with
/// C's printf(char*,...).

/// @fn auto dosdl2cpp::error::get() -> std::string_view
/// @brief Get the last error message.
/// @returns A std::string_view with the message with information about the
/// specific error that occurred, or an empty string if there hasn't been an
/// error message set since the last call to @ref dosdl2cpp::error::clear(). The
/// message is only applicable when an SDL function has signaled an error. You
/// must check the return values of SDL function calls to determine when to
/// appropriately call @ref dosdl2cpp::error::get().
/// @remarks It is possible for multiple errors to occur before calling @ref
/// dosdl2cpp::error::get(). Only the last error is returned.
/// @sa dosdl2cpp::error::set(std::string_view const& fmt,Args... args)
/// @sa dosdl2cpp::error::clear()
///
/// The message is only applicable when an SDL function has signaled an error.
/// You must check the return values of SDL function calls to determine when to
/// appropriately call @ref dosdl2cpp::error::get(). You should *not* use the
/// results of @ref dosdl2cpp::error::get() to decide if an error has occurred!
/// Sometimes SDL will set an error string even when reporting success.
///
/// SDL will *not* clear the error string for successful API calls. You *must*
/// check return values for failure cases before you can assume the error string
/// applies.
///
/// Error strings are set per-thread, so an error set in a different thread will
/// not interfere with the current thread's operation.
///
/// The returned string is internally allocated and must not be freed by the
/// application.

/// @fn auto dosdl2cpp::error::get_msg(std::array<char, BufferSize>& buffer) ->
/// std::array<char, BufferSize>
/// @brief Get the last error message that was set for the current thread.
/// @tparam BufferSize An std::size_t with the size of the buffer array.
/// @param buffer A std::array<char,BufferSize> with the buffer to put the error
/// message into.
/// @returns A std::array<char,BufferSize> with the passed in buffer message.
/// @sa dosdl2cpp::error::get()
/// @since SDL v2.0.14.
///
/// This allows the caller to copy the error string into a provided buffer, but
/// otherwise operates exactly the same as @ref dosdl2cpp::error::get().

/// @fn auto dosdl2cpp::error::clear() -> void
/// @brief Clear any previous error message for this thread.
/// @sa dosdl2cpp::error::get()
/// @sa dosdl2cpp::error::set(std::string_view const& fmt,Args... args)