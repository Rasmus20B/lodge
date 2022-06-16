#pragma once

#include "event.hpp"
#include "levels.hpp"
#include "macros.hpp"
#include "outputStream.hpp"
#include "printer.hpp"
#include "queue.hpp"
#include "queue_r.hpp"
#include "queue_w.hpp"

#include <fmt/core.h>
#include <string>
#include <string_view>

namespace lodge {

template <typename... Args>
auto debug(fmt::format_string<Args...> fmt, Args &&...args) {
  log(Level::LODGE_DEBUG, fmt, std::forward<Args>(args)...);
}

template <typename T> auto debug(const T msg) { log(Level::LODGE_DEBUG, msg); }

template <typename... Args>
auto log(Level level, fmt::format_string<Args...> fmt, Args &&...args) {

  std::cout << (int)level << std::endl;
  std::string buf =
      fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...));
  std::cout << buf << std::endl;
}

template <typename T> auto log(Level level, const T msg) {
  log(level, "{}", msg);
}
} // namespace lodge
