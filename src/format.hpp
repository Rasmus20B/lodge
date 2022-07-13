#pragma once

#include <experimental/source_location>
#include <fmt/core.h>

struct format_string {
  fmt::string_view str;
  std::experimental::source_location loc;

  format_string(const char *str,
                const std::experimental::source_location &loc =
                    std::experimental::source_location::current())
      : str(str), loc(loc) {}

  format_string(const char *str) : str(str) {}
};
