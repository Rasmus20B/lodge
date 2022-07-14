#pragma once

#include <chrono>
#include <experimental/source_location>
#include <iostream>
#include <string_view>

#include "levels.hpp"

namespace lodge {
struct log_item {
  log_item() = default;
  log_item(std::experimental::source_location loc, Level lvl, std::string msg)
      : loc(loc), level(lvl), buf(msg) {}

  std::chrono::time_point<std::chrono::system_clock> time =
      std::chrono::system_clock::now();
  std::experimental::source_location loc;
  Level level;
  std::string buf;
};
} // namespace lodge
