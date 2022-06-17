#pragma once

#include <experimental/source_location>
#include <string_view>

#include "levels.hpp"

namespace lodge {
struct log_item {
  log_item() = default;
  log_item(std::experimental::source_location loc, Level lvl, std::string msg)
      : loc(loc), level(lvl), buf(msg) {}

  std::experimental::source_location loc;
  Level level;
  std::string buf;
};
} // namespace lodge
