#pragma once

#include "levels.hpp"
#include "log_item.hpp"
#include "printer.hpp"
#include "queue.hpp"

#include <chrono>
#include <ctime>
#include <experimental/source_location>
#include <fmt/core.h>
#include <iomanip>
#include <iterator>
#include <string>
#include <string_view>
#include <thread>

namespace lodge {

class logger {

public:
  logger(const Level logger_level = default_log_level) noexcept {
    m_logLevel = logger_level;
  }

  static void log_thread_main() noexcept {
    log_item i = q.pop();
    return;
  };
  static void start() noexcept {
    log_thread = std::jthread(log_thread_main);
    return;
  }

  template <typename... Args>
  static void debug(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_DEBUG, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  static void warn(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_WARN, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  static void info(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_INFO, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  static void error(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_ERROR, fmt, std::forward<Args>(args)...);
  }

  // Auto argument type expands to template<Typename T> (C++20)
  static void debug(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  static void warn(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  static void info(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  static void error(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }

  template <typename... Args>
  static void log(Level level, fmt::format_string<Args...> fmt,
                  Args &&...args) noexcept {
    std::experimental::source_location loc{};
    log(loc, level, fmt, std::forward<Args>(args)...);
  }

  template <typename T> static void log(Level level, const T msg) noexcept {
    log(level, "{}", msg);
  }

  template <typename... Args>
  static void log(std::experimental::source_location loc, Level level,
                  fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    std::string buf{};
    fmt::vformat_to(std::back_inserter(buf), fmt,
                    fmt::make_format_args(std::forward<Args>(args)...));
    // Create a log item using the buffer and other args
    log_item log_item(loc, level, buf);
    // Pass the log message into final log function
    lprint(log_item);
  }

  static void setLogLevel(const Level level) noexcept { m_logLevel = level; }
  static void writeLogsToSinks();

private:
  static inline Level m_logLevel;
  static inline std::jthread log_thread;
  static lQueue<log_item, 64> q;
};

inline logger log;

} // namespace lodge
