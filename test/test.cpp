/*
bundle config --local path vendor/bundle
bundle install
bundle exec arduino_ci.rb --skip-examples-compilation
 */
#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "SD_CI.h"
#include "globals.h"
#include <fstream>

unittest(exists_works) {
  assertFalse(sd_ci.exists("noSuchFile.txt"));
  // existingFile.txt must obviously exist in fileSystem/
  // for this test to work. - LI
  assertTrue(sd_ci.exists("existingFile.txt"));
}

unittest(mkdir_works) {
  assertTrue(sd_ci.mkdir("new_directory"));
  assertTrue(sd_ci.mkdir("test_directory/a/b"));
  assertTrue(sd_ci.mkdir("test_directory/a/c"));
  assertTrue(sd_ci.exists("test_directory/a/b"));
  assertTrue(sd_ci.exists("test_directory/a/c"));
}

unittest(remove_works) {

}

unittest(rmdir_works) {
  assertTrue(sd_ci.rmdir("test_directory/a/b"));
  assertFalse(sd_ci.exists("test_directory/a/b"));
  assertTrue(sd_ci.rmdir("test_directory"));
  assertFalse(sd_ci.exists("test_directory"));
}

unittest(open_works) {

}

unittest_main()
