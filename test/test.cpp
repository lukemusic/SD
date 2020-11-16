/*
bundle config --local path vendor/bundle
bundle install
bundle exec arduino_ci.rb --skip-examples-compilation
 */
#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "SD.h"

unittest(test) {
  // add tests here
  assertTrue(true);
}

unittest_main()
