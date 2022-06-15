#pragma once

#include "levels.hpp"

namespace lodge {

struct Event {
  uint64_t id = {};
  Level level = Level::LODGE_DEBUG;
  std::string function;
  std::string type;
  std::string file;
};

} // namespace lodge
