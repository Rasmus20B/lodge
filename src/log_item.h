#pragma once

// #include <bits/chrono.h>
#include <chrono>
#include <compare>
#include <experimental/source_location>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <string_view>

#include "levels.h"

namespace lodge {
struct LogItem {
  LogItem() = default;
  explicit operator bool() const { return false; }

  LogItem(std::experimental::source_location loc, Level lvl,
          std::string_view msg)
      : loc{loc}, level{lvl}, buf{msg} {}

  friend auto operator<=>(const LogItem &lhs, const LogItem &rhs);

  friend bool operator==(const LogItem &rhs, const LogItem &lhs) {
    if (rhs.buf == lhs.buf) {
      if (rhs.level == lhs.level) {
        return true;
      }
    }
    return false;
  }

  std::experimental::source_location loc;
  Level level;
  std::string buf;
  std::time_t time = std::time(nullptr);
  std::string fmt_str{"[{}] {} : {}\n"};
};

} // namespace lodge
