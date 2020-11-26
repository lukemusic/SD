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
  File_CI existingFile = sd_ci.open("existingFile.txt", O_WRITE);
  existingFile.close();
  assertTrue(sd_ci.exists("existingFile.txt"));
  sd_ci.remove("existingFile.txt");
}

unittest(mkdir_works) {
  assertTrue(sd_ci.mkdir("test_directory/a/b"));
  assertTrue(sd_ci.mkdir("test_directory/a/c"));
  assertTrue(sd_ci.exists("test_directory"));
  assertTrue(sd_ci.exists("test_directory/a/b"));
  assertTrue(sd_ci.exists("test_directory/a/c"));

  // tear down
  sd_ci.rmdir("test_directory");
}

unittest(open_works) {
  // try to open read file that doesn't exist
  File_CI readFile = sd_ci.open("file.txt", O_READ);
  assertFalse(readFile.isOpen());

  // create file
  File_CI writeFile = sd_ci.open("file.txt", O_WRITE);
  writeFile.close();
  // open file for read should exist
  File_CI readFile2 = sd_ci.open("file.txt", O_READ);
  assertTrue(readFile2.isOpen());
  readFile2.close();
  // delete test file
  sd_ci.remove("file.txt");
}

unittest(close_works) {
  // close write file
  File_CI file = sd_ci.open("file.txt", O_WRITE);
  assertTrue(file.isOpen());
  file.close();
  assertFalse(file.isOpen());

  // close read file
  File_CI readFile = sd_ci.open("file.txt", O_READ);
  assertTrue(readFile.isOpen());
  readFile.close();
  assertFalse(readFile.isOpen());
  sd_ci.remove("file.txt");
}

unittest(remove_works) {
  // set up
  File_CI file = sd_ci.open("file.txt", O_WRITE);
  file.close();
  assertTrue(sd_ci.exists("file.txt"));

  sd_ci.remove("file.txt");
  assertFalse(sd_ci.exists("file.txt"));
}

unittest(rmdir_works) {
  // set up
  sd_ci.mkdir("test_directory/a/a");
  sd_ci.mkdir("test_directory/a/b");
  sd_ci.mkdir("test_directory/a/c");
  File_CI file = sd_ci.open("test_directory/a/a/file.txt", O_WRITE);
  file.close();

  // remove directory
  assertTrue(sd_ci.rmdir("test_directory/a/c"));
  // make sure non-removed dirs still exist
  assertTrue(sd_ci.exists("test_directory"));
  assertTrue(sd_ci.exists("test_directory/a/a"));
  // make sure removed dir no longer exists
  assertFalse(sd_ci.exists("test_directory/a/c"));

  // remove directory with sub directories
  assertTrue(sd_ci.rmdir("test_directory"));
  assertFalse(sd_ci.exists("test_directory"));
}

unittest(name_works) {
  // set up
  File_CI file = sd_ci.open("newFile.txt", O_WRITE);

  char expected[] = "newFile.txt";
  assertEqual(expected, file.name());
  file.close();

  // tear down
  sd_ci.remove("newFile.txt");
}

unittest(seek_works) {
  // set up
  File_CI file = sd_ci.open("seek.txt", O_WRITE);
  char write[] = "Hide and Seek.";
  file.write(write, sizeof(write) - 1);
  file.close();
  File_CI read = sd_ci.open("seek.txt", O_READ);

  // Testing
  char readFrom[100];
  char expected[] = "and";
  read.seek(5);
  read.read(readFrom, 3);
  assertEqual(expected, readFrom);

  // tear down
  sd_ci.remove("seek.txt");
}

unittest(read_works) {
  // set up
  File_CI file = sd_ci.open("birthday.txt", O_WRITE);
  char toWrite[] = "Happy Birthday to You!";
  file.write(toWrite, sizeof(toWrite) - 1);
  file.close();
  File_CI file2 = sd_ci.open("lines.txt", O_WRITE);
  char toWrite2[] = "line 1\nline2";
  file2.write(toWrite2, sizeof(toWrite2) - 1);
  file2.close();

  // testing
  File_CI readFile = sd_ci.open("birthday.txt", O_READ);
  char readFromFile[100];
  readFile.read(readFromFile, readFile.size());
  readFile.close();

  char expected[100] = "Happy Birthday to You!";
  assertEqual(expected, readFromFile);

  File_CI readFile2 = sd_ci.open("lines.txt", O_READ);
  char readFromFile2[100];
  char readFromFile3[100];
  readFile2.read(readFromFile2, 7);
  readFile2.read(readFromFile3, 5);

  char expected2[100] = "line 1\n";
  char expected3[100] = "line2";
  assertEqual(expected2, readFromFile2);
  assertEqual(expected3, readFromFile3);

  // tear down
  sd_ci.remove("birthday.txt");
  sd_ci.remove("lines.txt");
}

unittest(write_works) {
  // open new file for writing
  File_CI writeFile = sd_ci.open("wood.txt", O_WRITE);
  char toWrite[] = "How much wood could a wood pecker peck?\n";
  writeFile.write(toWrite, sizeof(toWrite) - 1);

  // read from same write file
  // char readFromFile[100];
  // writeFile.seek(0);
  // writeFile.read(readFromFile, writeFile.size());
  // assertEqual(toWrite, readFromFile);
  // writeFile.close();

  // read from new read file
  writeFile.close();
  File_CI readWrite = sd_ci.open("wood.txt", O_READ);
  char toRead[100];
  readWrite.read(toRead, readWrite.size());
  char expected[100] = "How much wood could a wood pecker peck?\n";
  assertEqual(expected, toRead);
  readWrite.close();

  // open old writing file to write at end.
  File_CI writeFile2 = sd_ci.open("wood.txt", O_WRITE);
  char toWrite2[] = "A lot of wood.\n";
  writeFile2.write(toWrite2, sizeof(toWrite2) - 1);
  writeFile2.close();

  // check old writing file
  // File_CI readWrite2 = sd_ci.open("wood.txt", O_READ);
  // char toRead2[100];
  // readWrite2.read(toRead2, readWrite2.size());
  // char expected2[100] = "How much wood could a wood pecker peck?\nA lot of wood.\n";
  // assertEqual(expected2, toRead2);
  // readWrite2.close();

  // try writing to read only file
  File_CI readFile = sd_ci.open("wood.txt", O_READ);
  char toWrite3[] = "This should not go in file";
  assertEqual(0, readFile.write(toWrite3, sizeof(toWrite3) - 1));

  // teardown
  sd_ci.remove("wood.txt");
}

unittest(size_works) {
  // setup
  File_CI sizeFile = sd_ci.open("size.txt", O_WRITE);
  char toWrite[] = "Test text\n";
  sizeFile.write(toWrite, sizeof(toWrite) - 1);
  sizeFile.close();

  // test
  uint32_t fileSize = sizeFile.size();
  assertEqual(10, fileSize);

  // tear down
  sd_ci.remove("size.txt");
}

unittest(peek_works) {
  // set up
  File_CI peekFile = sd_ci.open("peek.txt", O_WRITE);
  char toWrite[] = "Peek file content\n";
  peekFile.write(toWrite, sizeof(toWrite) - 1);
  peekFile.close();

  // Test
  File_CI readPeek = sd_ci.open("peek.txt", O_READ);
  assertEqual('P', readPeek.peek());
  assertEqual('P', readPeek.peek());
  readPeek.close();

  // tear down
  sd_ci.remove("peek.txt");
}


unittest_main()


/*
Issues
1. Can't read from appended file. It adds some
   binary giberisth at the end.
2. Can't read from write file even though it's
   fstream and not exclusively ofstream

*/