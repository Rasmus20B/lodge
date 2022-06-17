#pragma once

#include "levels.hpp"
#include "log_item.hpp"

#include <chrono>
#include <ctime>
#include <experimental/source_location>
#include <fmt/core.h>
#include <iomanip>
#include <iterator>
#include <string>
#include <string_view>

namespace lodge {

template <typename... Args>
auto debug(fmt::format_string<Args...> fmt, Args &&...args) {
  log(Level::LODGE_DEBUG, fmt, std::forward<Args>(args)...);
}
template <typename... Args>
auto warn(fmt::format_string<Args...> fmt, Args &&...args) {
  log(Level::LODGE_WARN, fmt, std::forward<Args>(args)...);
}
template <typename... Args>
auto info(fmt::format_string<Args...> fmt, Args &&...args) {
  log(Level::LODGE_INFO, fmt, std::forward<Args>(args)...);
}
template <typename... Args>
auto error(fmt::format_string<Args...> fmt, Args &&...args) {
  log(Level::LODGE_ERROR, fmt, std::forward<Args>(args)...);
}
template <typename T> auto debug(const T msg) { log(Level::LODGE_DEBUG, msg); }
template <typename T> auto warn(const T msg) { log(Level::LODGE_DEBUG, msg); }
template <typename T> auto info(const T msg) { log(Level::LODGE_DEBUG, msg); }
template <typename T> auto error(const T msg) { log(Level::LODGE_DEBUG, msg); }

template <typename... Args>
auto log(Level level, fmt::format_string<Args...> fmt, Args &&...args) {
  std::experimental::source_location loc{};

  log(loc, level, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
auto log(std::experimental::source_location loc, Level level,
         fmt::format_string<Args...> fmt, Args &&...args) {

  log(std::chrono::system_clock::now(), loc, level, fmt,
      std::forward<Args>(args)...);
}

template <typename T> auto log(Level level, const T msg) {
  log(level, "{}", msg);
}

template <typename T> auto log(log_item item) {
  std::cout << item.loc.file_name() << ' ' << int(item.level) << ' ' << item.buf
            << std::endl;
}

template <typename... Args>
auto log(std::chrono::time_point<std::chrono::system_clock> time,
         std::experimental::source_location loc, Level level,
         fmt::format_string<Args...> fmt, Args &&...args) {
  std::string buf{};
  fmt::vformat_to(std::back_inserter(buf), fmt,
                  fmt::make_format_args(std::forward<Args>(args)...));
  // Create a log item using the buffer and other args
  log_item log_item(loc, level, buf);
  // Pass the log message into final log template
  std::string_view log_name = to_string_view(log_item.level);
  std::cout << ':' << log_name << ':' << log_item.loc.file_name() << ':'
            << log_item.buf << std::endl;
}

} // namespace lodge
