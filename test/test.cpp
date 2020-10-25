/*
bundle config --local path vendor/bundle
bundle install
bundle exec arduino_ci_remote.rb  --skip-compilation
bundle exec arduino_ci_remote.rb  --skip-unittests
 */
#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "SD.h"

unittest(test) {
  // add tests here
  assertTrue(true);
}

unittest_main()
