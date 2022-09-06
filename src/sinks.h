#pragma once

#include <fmt/core.h>
#include <functional>
#include <string_view>

#include "levels.h"
#include "log_item.h"

namespace lodge {

template <typename T> struct Sink {
  T func{};
  std::string_view name{};
};

void sinkStdio(const LogItem &i);

} // namespace lodge
