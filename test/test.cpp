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

// unittest(exists_works) {
//   assertFalse(sd_ci.exists("noSuchFile.txt"));
//   // existingFile.txt must obviously exist in fileSystem/
//   // for this test to work. - LI
//   assertTrue(sd_ci.exists("existingFile.txt"));
// }

// unittest(mkdir_works) {
//   assertTrue(sd_ci.mkdir("new_directory"));
//   assertTrue(sd_ci.mkdir("test_directory/a/b"));
//   assertTrue(sd_ci.mkdir("test_directory/a/c"));
//   assertTrue(sd_ci.exists("test_directory/a/b"));
//   assertTrue(sd_ci.exists("test_directory/a/c"));
// }

// unittest(rmdir_works) {
//   assertTrue(sd_ci.rmdir("test_directory/a/b"));
//   assertFalse(sd_ci.exists("test_directory/a/b"));
//   assertTrue(sd_ci.rmdir("test_directory"));
//   assertFalse(sd_ci.exists("test_directory"));
// }

// File_CI testFile = sd_ci.open("hello.txt", O_WRITE);
// unittest(open_works) { assertTrue(sd_ci.exists("hello.txt")); }

// unittest(name_works) {
//   char name[100] = "hello.txt";
//   assertEqual(*name, *testFile.name());
// }

// unittest(close_works) {
//   testFile.close();
//   assertFalse(testFile.isOpen());
// }

// unittest(remove_works) {
//   // testFile.close();
//   sd_ci.remove("hello.txt");
//   assertFalse(sd_ci.exists("hello.txt"));
// }

unittest(write_works) {
  sd_ci.remove("write.txt");
  File_CI writeFile = sd_ci.open("write.txt", O_WRITE);
  char toWrite[] = "How much wood could a wood pecker peck?\n";
  std::cout << "size: " << sizeof(toWrite) << " : " << writeFile << std::endl;
  // // writeFile.write(toWrite, sizeof(toWrite));
  // writeFile.close();
}

// unittest(size_works) {
//   sd_ci.remove("size.txt");
//   File_CI sizeFile = sd_ci.open("size.txt", O_WRITE);
//   sizeFile.write1("This is a file with some text in it for testing.");
//   uint32_t fileSize = sizeFile.size();
//   assertEqual(49, fileSize);
// }

unittest_main()
