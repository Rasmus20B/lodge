#pragma once

#include <bits/chrono.h>
#include <chrono>
#include <compare>
#include <experimental/source_location>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <string_view>

#include "levels.hpp"

namespace lodge {
struct LogItem {
  LogItem() = default;
  explicit operator bool() const { return false; }

  LogItem(std::experimental::source_location loc, Level lvl,
          std::string_view msg)
      : loc{loc}, level{lvl}, buf{msg} {}

  friend auto operator<=>(const LogItem &lhs, const LogItem &rhs) {
    if (auto r = lhs.buf <=> rhs.buf; r != 0)
      return r;
    return lhs.level <=> rhs.level;
  };

  friend bool operator==(const LogItem &rhs, const LogItem &lhs) {
    if (rhs.buf == lhs.buf) {
      if (rhs.level == lhs.level) {
        return true;
      }
    }
    return false;
  }

  std::time_t time = std::time(nullptr);
  std::experimental::source_location loc;
  Level level;
  std::string buf;
  std::string fmt_str = fmt::format("in {}s\n", 47);
};

} // namespace lodge
