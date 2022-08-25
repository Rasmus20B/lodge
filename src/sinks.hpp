#pragma once

#include <fmt/core.h>
#include <functional>
#include <string_view>

#include "levels.hpp"
#include "log_item.hpp"

namespace lodge {

template <typename T> struct Sink {
  T func{};
  std::string_view name{};
};

static void sinkStdio(const LogItem &i) {
  fmt::print(fmt::runtime(i.fmt_str), i.time, to_string_view(i.level), i.buf);
}
// This is where new sink functions can go

} // namespace lodge
