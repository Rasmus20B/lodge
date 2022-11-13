#include "sinks.h"

namespace lodge {
void sinkStdio(const LogItem &i) {
  fmt::print(fmt::runtime(i.fmt_str), i.time, to_string_view(i.level), i.buf);
}

void sinkColorStdio(const LogItem &i) {
  fmt::print(fmt::runtime(i.fmt_str), i.time, to_string_view(i.level), i.buf);
}

void sinkFile(const LogItem &i) {
  std::ofstream f;
  f.open("log.txt", std::iostream::ios_base::app);

  fmt::print(f, (i.fmt_str), i.time, to_string_view(i.level), i.buf);
  f.close();
}

/* Add Any new Sinks here */
} // namespace lodge
