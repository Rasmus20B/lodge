#include "../src/lodge.hpp"
#include "fmt/core.h"

int main() {
  lodge::info("Hello {}", "World");
  lodge::error("Hello {}", "World");
  lodge::warn("Hello {}", "World");
  lodge::debug("THIS IS A SINGLE PARAMETER");
}
