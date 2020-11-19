#include "SD_CI.h"
#include "globals.h"
#ifdef ARDUINO_CI

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

namespace SDLib {

// File_CI::File_CI(File_Base *baseFile) {
//   // this->baseFile = baseFile;
// }

// File_CI::File_CI(SdFile f, const char *name) : File_Base(f, name) {}

// File_CI::File_CI(void) : File_Base() {}

File_CI::File_CI(const char *name, uint8_t mode) {
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, name);

  if (mode == O_READ) {
    fin = new std::ifstream;
    fin->open(newPath, std::ios::binary | std::ios::in);
  } else {
    // mode == O_WRITE
    finOut = new std::fstream;
    finOut->open(newPath, std::ios::binary | std::ios::ate | std::ios::out);
  }

  _mode = mode;
  _fileName = new char[100];
  strcpy(_fileName, name);
  _open = true;
}

File_CI::~File_CI() {
  delete finOut;
  delete fin;
  delete _fileName;
}

// size_t File_CI::write(uint8_t value) { return File_Base::write(value); }

size_t File_CI::write(const char *buf, size_t size) {
  finOut->write(buf, size);
  return size;
}

int File_CI::availableForWrite() { return File_Base::availableForWrite(); }

int File_CI::read() {
  //   int baseResult = baseFile->read();
  // read from local file system HERE
  return 'a';
}

int File_CI::peek() { return File_Base::peek(); }

int File_CI::available() {
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);

  return fs::file_size(newPath);
}

void File_CI::flush() { return File_Base::flush(); }

int File_CI::read(void *buf, uint16_t nbyte) {
  return File_Base::read(buf, nbyte);
}

bool File_CI::seek(uint32_t pos) { return File_Base::seek(pos); }

uint32_t File_CI::position() { return File_Base::position(); }

uint32_t File_CI::size() {
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);
  std::cout << "about to call file_size" << std::endl;
  return fs::file_size(newPath);
}

void File_CI::close() {
  // read mode
  if (_mode == O_READ) {
    fin->close();
  } else {
    // write mode
    finOut->close();
  }
  _open = false;
}

File_CI::operator bool() { return File_Base::operator bool(); }

char *File_CI::name() { return _fileName; }

bool File_CI::isDirectory(void) { return File_Base::isDirectory(); }

} // namespace SDLib

#endif
