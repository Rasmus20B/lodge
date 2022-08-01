#pragma once

#include <fmt/core.h>
#include <functional>
#include <string_view>

#include "log_item.hpp"

namespace lodge {

// #ifdef USE_FUNCTION
// struct sinks {
//   std::vector<std::function<void(lodge::log_item)>> func{};
//   std::vector<std::string_view> name{};
//   void invoke_all(log_item item) {
//     for (auto &&i : func) {
//       i(item);
//     }
//   }
// };
// #else
// struct sinks {
//   std::vector<void (*)(log_item)> func{};
//   std::vector<std::string_view> name{};

//   void invoke_all(log_item item) {
//     for (auto &&i : func) {
//       i(item);
//     }
//   }
// };
// #endif

template <typename T> struct sinks {

  std::vector<T> func{};
  std::vector<std::string_view> name{};

  void invoke_all(LogItem &item) {
    std::cout << "gets to invoke function\n";
    for (auto &i : func) {
      i(item);
    }
  }
};

static void sinkStdio(const LogItem &i) {

  fmt::print(fmt::runtime("{}"), i.buf);

  std::cout << i.time << " [" << to_string_view(i.level) << "] " << i.buf
            << std::endl;
  return;
}
// This is where new sink functions can go

} // namespace lodge
