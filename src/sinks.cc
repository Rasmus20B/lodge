#include "sinks.h"

namespace lodge {
  void sinkStdio(const LogItem &i) {
    fmt::print(fmt::runtime(i.fmt_str), i.time, to_string_view(i.level), i.buf);
  }

/* Add Any new Sinks here */
}
