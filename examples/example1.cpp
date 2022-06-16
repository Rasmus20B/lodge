#include "../src/lodge.hpp"
#include "fmt/core.h"

int main() {
  lodge::debug("Hello {}", "World");
  lodge::debug("THIS IS A SINGLE PARAMETER");
}
