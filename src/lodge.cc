#include "lodge.h"

namespace lodge {

  Logger::Logger(const Level logger_level) noexcept {
    m_logLevel = logger_level;
  }

  void Logger::log_thread_main(std::stop_token tk) noexcept {

    // Flush the Queue on a timer
    using namespace std::chrono_literals;

    while (!tk.stop_requested()) {
      std::optional<LogItem> i = q.try_pop();

      if (i.has_value()) {
        writeLogToSinks(i.value());
      }
      std::this_thread::sleep_for(10ms);
    }
  }

  void Logger::start() noexcept {
    addSink(sinkStdio, "stdio");
    log_thread = std::jthread(&Logger::log_thread_main, this, ss.get_token() );
  }

   void Logger::stop() noexcept {
     log_thread.request_stop();
     log_thread.join();
   }

  

  void Logger::setLogLevel(const Level level) noexcept { m_logLevel = level; }

  void Logger::addSink(const std::function<void(const LogItem &)> function,
               const std::string_view name) noexcept {

    Sink<std::function<void(const LogItem &)>> ls{function, name};
    s.push_back(ls);
  }

  void Logger::writeLogToSinks(const LogItem &i) noexcept {

    for (auto &j : s) {
      j.func(i);
    }
  }

} // namespace lodge
