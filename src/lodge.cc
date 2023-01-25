#include "lodge.h"

namespace lodge {

Logger::Logger(const Level logger_level) noexcept { m_logLevel = logger_level; }

void Logger::log_thread_main() noexcept {

  // Flush the Queue on a timer
  using namespace std::chrono_literals;

  while (!ss.get_token().stop_requested() || !q.empty()) {
    std::optional<LogItem> i = q.try_pop();
    if (i.has_value()) {
      writeLogToSinks(i.value());
    }
  }
  return;
}

void Logger::start() noexcept {
  addSink(sinkStdio, "stdio");
  log_thread = std::jthread(&Logger::log_thread_main, this);
}

void Logger::stop() noexcept {
  if(log_thread.joinable()) {
    ss.request_stop();
    log_thread.join();
  }
}

void Logger::setLogLevel(const Level level) noexcept { m_logLevel = level; }

void Logger::addSink(void f(const LogItem &), const std::string_view name) noexcept {
  Sink<void (*)(const LogItem &)> ls{f, name};
  s.push_back(ls);
}
void Logger::writeLogToSinks(const LogItem &i) noexcept {
  for (auto &j : s) {
    j.func(i);
  }
}

} // namespace lodge
