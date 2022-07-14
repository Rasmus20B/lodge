#include "../src/lodge.hpp"
#include "fmt/core.h"

int main() {
  lodge::log.start();
  lodge::log.info("Hello {}", "World");
  lodge::log.error("Hello {}, {} {}", "World", 3, "arguments");
  // Should not print "World"
  lodge::log.warn("Hello ", "World");
  lodge::log.debug("THIS IS A SINGLE PARAMETER");
  lodge::log.debug("asdf");
  lodge::log.debug("{}", "asdfasdfasdfSD");
  lodge::log.debug("{} of them", 6);
}
