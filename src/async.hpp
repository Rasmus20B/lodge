#pragma once

#include "levels.hpp"
#include "queue.hpp"
#include <memory>
#include <thread>

// namespace lodge {

// class logger {

// public:
//   logger();
//   static void start(Level level = default_log_level) {
//     auto log_thread = std::jthread(main_log_thread);
//     return;
//   }
//   void flush();

// private:
//   static void main_log_thread();
//   std::jthread m_log_thread;
//   std::shared_ptr<Queue> m_fifo;
// };

// inline logger logger;

// } // namespace lodge
