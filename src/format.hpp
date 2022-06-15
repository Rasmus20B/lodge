
#include <fmt/core.h>
#include <source_location>

struct format_string {
  fmt::string_view str;
  std::source_location loc;

  format_string(const char *str, const std::source_location &loc =
                                     std::source_location::current())
      : str(str), loc(loc) {}
};
