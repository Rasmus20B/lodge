#pragma once

#include <fmt/core.h>
#include <iostream>

#include <string_view>

namespace lodge {
enum class Level {
  LODGE_INFO = 0,
  LODGE_DEBUG = 1,
  LODGE_WARN = 2,
  LODGE_ERROR = 3,
  LODGE_COUNT = 4
};

#define LODGE_NAME_INFO std::string_view("INFO", 4)
#define LODGE_NAME_DEBUG std::string_view("DEBUG", 5)
#define LODGE_NAME_WARNING std::string_view("WARNING", 7)
#define LODGE_NAME_ERROR std::string_view("ERROR", 5)

#define LODGE_LEVEL_NAMES                                                      \
  { LODGE_NAME_INFO, LODGE_NAME_DEBUG, LODGE_NAME_WARNING, LODGE_NAME_ERROR }

static const std::string_view level_names_strings[] LODGE_LEVEL_NAMES;

static inline const std::string_view &to_string_view(Level level) noexcept {
  return level_names_strings[static_cast<int>(level)];
}
} // namespace lodge
