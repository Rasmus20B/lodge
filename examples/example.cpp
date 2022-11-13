#include "../src/lodge.h"

int main() {
  lodge::log.start();
  lodge::log.addSink(lodge::sinkFile, "file");
  lodge::log.info("Hello {}", "World");
  lodge::log.error("Hello {}, {} {}", "World", 3, "arguments");
  // Should not print "World"
  lodge::log.warn("Hello ", "World");
  lodge::log.debug("THIS IS  ", 3);
  lodge::log.debug("asdf");
  lodge::log.debug("{}", "asdfasdfasdfSDasdasd");
  lodge::log.debug("{} of them", 6);
  lodge::log.stop();
}
