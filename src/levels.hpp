#pragma once

#include <iostream>

namespace lodge {
enum class Level { LODGE_INFO, LODGE_ERROR, LODGE_WARN, LODGE_DEBUG };
template <typename T> void log(Level level, std::string method, T message);
} // namespace lodge
