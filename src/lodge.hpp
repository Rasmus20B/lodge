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

  void log_thread_main() noexcept {

    // Flush the Queue on a timer
    using namespace std::chrono_literals;
    while (1) {
      std::optional<log_item> i(q.try_pop());
      // std::cout << i->time.time_since_epoch() << " : "
      //           << to_string_view(i->level) << " " << i->buf << "\n";

      if (i.has_value()) {

        // writeLogToSinks(i.value());
        sf(i.value());
      }
      std::this_thread::sleep_for(100ms);
    }
    return;
  };

  void start() noexcept {
    addSink(sinkStdio, "stdio");
    log_thread = std::jthread(&logger::log_thread_main, this);
    return;
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

  template <typename... Args>
  void log(std::experimental::source_location loc, Level level,
           fmt::format_string<Args...> fmt, Args &&...args) noexcept {
    std::string buf{};
    fmt::vformat_to(std::back_inserter(buf), fmt,
                    fmt::make_format_args(std::forward<Args>(args)...));
    // Create a log item using the buffer and other args
    log_item log_item(loc, level, buf);

    q.push(log_item);
  }

  // void final_log(log_item i) {}

  void setLogLevel(const Level level) noexcept { m_logLevel = level; }

#ifdef USE_FUNCTION
  void addSink(const std::function<(void)(log_item)> function,
               const std::string_view name) {
    s.name.push_back(name);
    s.func.push_back(function);
  }
#else
  void addSink(void (*function)(log_item), const std::string_view name) {
    s.name.push_back(name);
    s.func.push_back(function);
  }
#endif

  void printSinkNames() {
    for (auto &i : s.name) {
      std::cout << i << "\n";
    }
  }

  void writeLogToSinks(log_item &i) noexcept {

    sf(i);
    // s.invoke_all(i);
    return;
  }

private:
  Level m_logLevel;
  std::jthread log_thread;
  lQueue<log_item, 128> q;
  sinks<void (*)(log_item)> s{};
  void (*sf)(log_item) = sinkStdio;
};

inline logger log;

} // namespace lodge
