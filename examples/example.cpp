#include "lodge.hpp"

int main() {

  lodge::log.start();
  lodge::log.info("Hello {}", "World");
  lodge::log.error("Hello {}, {} {}", "World", 3, "arguments");
  // Should not print "World"
  lodge::log.warn("Hello ", "World");
  lodge::log.debug("THIS IS  ");
  lodge::log.debug("asdf");
  lodge::log.debug("{}", "asdfasdfasdfSDasdasd");
  lodge::log.debug("{} of them", 6);
  lodge::log.stop();
}
