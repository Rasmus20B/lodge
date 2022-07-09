#pragma once

#include <array>
#include <fmt/core.h>
#include <iostream>

#include <string_view>

namespace lodge {
enum class Level {
  LODGE_INFO,
  LODGE_DEBUG,
  LODGE_WARN,
  LODGE_ERROR,
  LODGE_COUNT
};

constexpr std::string_view LODGE_NAME_INFO = std::string_view("INFO", 4);
constexpr std::string_view LODGE_NAME_DEBUG = std::string_view("DEBUG", 5);
constexpr std::string_view LODGE_NAME_WARNING = std::string_view("WARNING", 7);
constexpr std::string_view LODGE_NAME_ERROR = std::string_view("ERROR", 5);

constexpr Level default_log_level = Level::LODGE_INFO;

constexpr std::array<std::string_view,
                     static_cast<std::size_t>(Level::LODGE_COUNT)>
    LODGE_LEVEL_NAMES = {LODGE_NAME_INFO, LODGE_NAME_DEBUG, LODGE_NAME_WARNING,
                         LODGE_NAME_ERROR};

inline const constexpr std::string_view &to_string_view(Level level) noexcept {
  return LODGE_LEVEL_NAMES.at(static_cast<int>(level));
}
} // namespace lodge
