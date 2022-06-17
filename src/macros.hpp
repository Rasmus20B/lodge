#pragma once

#include <source_location>

namespace lodge {

#define LODGE_DEBUG(...) log(LODGE_DEBUG, __FILE__, __func__, __LINE__, ...)
#define LODGE_WARN(...) log(LODGE_INFO, __FILE__, __func__, __LINE__, ...)
#define LODGE_ERROR(...)
#define LODGR_INFO(...)

} // namespace lodge
