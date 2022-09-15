#pragma once

#include <thread> 
#include <functional>
#include <experimental/source_location> 
#include <string_view>
#include <iomanip>
#include <chrono> 

#include <fmt/core.h>

#include "levels.h"
#include "log_item.h"
#include "queue.h"
#include "sinks.h"

namespace lodge {
  class Logger {
  public:
    Logger(const Level logger_level = default_log_level) noexcept;
    void log_thread_main(std::stop_token tk) noexcept;
    void start() noexcept;
    void stop() noexcept;

    
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
    void warn(const auto msg) noexcept { log(Level::LODGE_WARN, msg); }
    void info(const auto msg) noexcept { log(Level::LODGE_INFO, msg); }
    void error(const auto msg) noexcept { log(Level::LODGE_ERROR, msg); }

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
      LogItem i(loc, level, buf);

      q.push(i);
    }

  private:
    void setLogLevel(const Level l) noexcept;

#ifdef USE_STD_FUNCTION
    void addSink(const std::function<void(const LogItem &)> function, const std::string_view name) noexcept;
#else
    void addSink(void f(const LogItem&), const std::string_view name) noexcept;
#endif
    void writeLogToSinks(const LogItem &i) noexcept;

  private:
    Level m_logLevel;
    std::jthread log_thread;
    std::stop_source ss;
    lQueue<LogItem, 128> q;

#ifdef USE_STD_FUNCTION
    std::vector<Sink<std::function<void(const LogItem &)>>> s{};
#else
    std::vector<Sink<void (*)(const LogItem &)>> s{};
#endif

  };
inline Logger log;
}
