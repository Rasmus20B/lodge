#pragma once

#include <string>

namespace lodge {

typedef struct outputStream {
  std::ostream &out;
  std::string format = "";
} outputStream;
} // namespace lodge
