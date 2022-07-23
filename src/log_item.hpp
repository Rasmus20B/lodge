#pragma once

#include <bits/chrono.h>
#include <chrono>
#include <experimental/source_location>
#include <iostream>
#include <string_view>

#include "levels.hpp"

namespace lodge {
struct log_item {
  log_item() = default;
  explicit operator bool() const { return false; }

  log_item(std::experimental::source_location loc, Level lvl,
           std::string_view msg)
      : loc(loc), level(lvl), buf(msg) {}

  std::time_t time = std::time(nullptr);
  std::experimental::source_location loc;
  Level level;
  std::string buf;
};
} // namespace lodge
