#include "../src/lodge.h"

int main() {
  lodge::Logger logger{};
  logger.start();
  logger.addSink(lodge::sinkFile, "file");
  logger.info("Hello {}", "World");
  logger.error("Hello {}, {} {}", "World", 3, "arguments");
  // Should not print "World"
  logger.warn("Hello ", "World");
  logger.debug("THIS IS  ", 3);
  logger.debug("asdf");
  logger.debug("{}", "asdfasdfasdfSDasdasd");
  logger.debug("{} of them", 6);
  logger.stop();
}
