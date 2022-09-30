#include "lodge.h"

namespace lodge {

Logger::Logger(const Level logger_level) noexcept { m_logLevel = logger_level; }

void Logger::log_thread_main() noexcept {

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

#ifdef USE_STD_FUNCTION
void Logger::addSink(const std::function<void(const LogItem &)> function,
                     const std::string_view name) noexcept {

  Sink<std::function<void(const LogItem &)>> ls{function, name};
  s.push_back(ls);
}
#else
void Logger::addSink(void f(const LogItem &),
                     const std::string_view name) noexcept {
  Sink<void (*)(const LogItem &)> ls{f, name};
  s.push_back(ls);
}
#endif
void Logger::writeLogToSinks(const LogItem &i) noexcept {

  for (auto &j : s) {
    j.func(i);
  }
}

} // namespace lodge
