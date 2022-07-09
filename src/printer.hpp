#pragma once

#include "log_item.hpp"
#include <chrono>
#include <iomanip>

namespace lodge {

static void lprint(log_item item) {

  std::string_view log_name = to_string_view(item.level);
  std::cout << item.time.time_since_epoch().count() << ":" << log_name << ':'
            << item.loc.function_name() << ':' << item.buf << std::endl;

  return;
}

} // namespace lodge
