#pragma once

#include <concepts>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fstream>
#include <functional>
#include <string_view>
#include <type_traits>

#include "levels.h"
#include "log_item.h"

namespace lodge {

template <typename T> 
  requires(std::invocable<T&, const LogItem&>)
struct Sink {
  T func{};
  std::string_view name{};
};
void sinkStdio(const LogItem &i);
void sinkColourStdio(const LogItem &i);
void sinkFile(const LogItem &i);
} // namespace lodge
