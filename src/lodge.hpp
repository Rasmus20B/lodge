#pragma once

#include "levels.hpp"
#include "log_item.hpp"
#include "queue.hpp"
#include "sinks.hpp"

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

  void log_thread_main(std::stop_token tk) noexcept {

    // Flush the Queue on a timer
    using namespace std::chrono_literals;

    while (!tk.stop_requested()) {
      std::optional<LogItem> i = q.try_pop();

      if (i.has_value()) {
        writeLogToSinks(i.value());
      }
      std::this_thread::sleep_for(100ms);
    }
    info("Logging has stopped");
  }

  void start() noexcept {
    addSink(sinkStdio, "stdio");
    log_thread = std::jthread(&logger::log_thread_main, this, ss.get_token() );
  }

   void stop() noexcept {
     log_thread.request_stop();
     log_thread.join();
   }

  template <typename... Args>
  void debug(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_DEBUG, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  void warn(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_WARN, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  void info(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_INFO, fmt, std::forward<Args>(args)...);
  }
  template <typename... Args>
  void error(fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    log(Level::LODGE_ERROR, fmt, std::forward<Args>(args)...);
  }

  // Auto argument type expands to template<Typename T> (C++20)
  void debug(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  void warn(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  void info(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }
  void error(const auto msg) noexcept { log(Level::LODGE_DEBUG, msg); }

  template <typename... Args>
  void log(Level level, fmt::format_string<Args...> fmt,
           Args &&...args) noexcept {
    std::experimental::source_location loc{};
    log(loc, level, fmt, std::forward<Args>(args)...);
  }

  template <typename T> void log(Level level, const T msg) noexcept {
    log(level, "{}", msg);
  }

  /* Buffer on heap are not being correctly transferred to Queue (SSO works) */
  template <typename... Args>
  void log(std::experimental::source_location loc, Level level,
           fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    std::string buf{};
    fmt::vformat_to(std::back_inserter(buf), fmt,
                    fmt::make_format_args(std::forward<Args>(args)...));
    // Create a log item using the buffer and other args
    LogItem i(loc, level, buf);

    q.push(i);
  }

  void setLogLevel(const Level level) noexcept { m_logLevel = level; }

  void addSink(const std::function<void(const LogItem &)> function,
               const std::string_view name) {

    Sink<std::function<void(const LogItem &)>> ls{function, name};
    s.push_back(ls);
  }

  void writeLogToSinks(const LogItem &i) noexcept {

    for (auto &j : s) {
      j.func(i);
    }
  }

private:
  Level m_logLevel;
  std::jthread log_thread;
  std::stop_source ss;
  lQueue<LogItem, 128> q;
  std::vector<Sink<std::function<void(const LogItem &)>>> s{};
};

inline logger log;

} // namespace lodge
