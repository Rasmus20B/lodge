#pragma once

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

  void invoke_all(log_item &item) {
    std::cout << "gets to invoke function\n";
    for (auto &i : func) {
      std::cout << item.buf << '\n';
      // i(item);
    }
  }
};

static void sinkStdio(const log_item i) {

  std::cout << "HERESDF\n";

  std::cout << i.time.time_since_epoch() << " : " << to_string_view(i.level)
            << " " << i.buf << "\n";

  return;
}
// This is where new sink functions can go

} // namespace lodge
