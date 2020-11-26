#include "SD_CI.h"
#include "globals.h"
#ifdef ARDUINO_CI

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <cassert>
// #include <vector>

namespace SDLib {

// File_CI::File_CI(File_Base *baseFile) {
//   // this->baseFile = baseFile;
// }

// File_CI::File_CI(SdFile f, const char *name) : File_Base(f, name) {}

// File_CI::File_CI(void) : File_Base() {}

File_CI::File_CI(const char *name, uint8_t mode = FILE_READ) {
  _mode = mode;
  strcpy(_fileName, name);
  // does path exist?
    // if so, is it a directory?
      // if so, return a new object with the _isDirectory flag set

  // std::cout << "file object created" << std::endl;
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, name);
  // std::cout << "string length: " << strlen(newPath) << std::endl;
  // std::cout << '\"' << newPath << '\"' << std::endl;
  if (mode == FILE_READ) {
    fin = new std::ifstream;
    fin->open(newPath, std::ios::binary | std::ios::in);
    // std::cout << "fin open: " << fin->is_open() << std::endl;
    if (fin->fail()) {
      switch (errno) {
      case ENOENT:
        std::cout << "Could not find this file" << std::endl;
        break;
      default:
        perror("opening data file");
      }
      _open = false;
    } else {
      _open = true;
      _pos = 0;
    }
  } else {
    // mode == O_WRITE
    finOut = new std::fstream;
    // file already exists, get size
    if (fs::exists(newPath)) {
      _pos = 0;
      finOut->open(newPath);
    } else {
      _pos = 0;
      finOut->open(newPath, std::ios::binary | std::ios::out);
    }
    finOut->seekg(_pos);
    _open = true;
  }
}

File_CI::~File_CI() {
  // std::cout << "file object about to be deleted" << std::endl;
  if (_mode == O_WRITE) {
    delete finOut;
  }
  if (_mode == FILE_READ) {
    delete fin;
  }
  // std::cout << "file object deleted" << std::endl;
}

// size_t File_CI::write(uint8_t value) { return File_Base::write(value); }

size_t File_CI::write(const char *buf, size_t size) {
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);

  assert(_mode == O_WRITE);
  _pos = fs::file_size(newPath);
  finOut->seekg(_pos);
  finOut->write(buf, size);
  _pos = finOut->tellg();
  return size;
}

int File_CI::availableForWrite() { return File_Base::availableForWrite(); }

int File_CI::read(char *buf, size_t size) {
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);

  if (_mode == FILE_READ) {
    fin->seekg(_pos);
    fin->read(buf, size);
    _pos = fin->tellg();
  } else {
    std::cout << "Reading from write file" << std::endl;
    std::cout << "File pos: " << finOut->tellg() << std::endl;
    finOut->read(buf, size);
    _pos = finOut->tellg();
  }
  return 0;
}

int File_CI::peek() {
  char byte[1];
  if (_mode == FILE_READ) {
    fin->seekg(_pos);
    fin->read(byte, 1);
    // put file pointer back
    fin->seekg(_pos);
  }
  return (int)byte[0];
}

int File_CI::available() {
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);

  return fs::file_size(newPath);
}

void File_CI::flush() { return File_Base::flush(); }

bool File_CI::seek(uint32_t pos) {
  _pos = pos;
  if (_mode == FILE_READ) {
    fin->seekg(pos);
  } else {
    finOut->seekg(pos);
  }
  return true;
}

uint32_t File_CI::position() { return _pos; }

uint32_t File_CI::size() {
  // prepend base file path
  char newPath[100];
  strcpy(newPath, BASE_PATH);
  strcat(newPath, _fileName);
  return fs::file_size(newPath);
}

void File_CI::close() {
  // read mode
  if (_mode == FILE_READ) {
    fin->close();
  } else {
    // write mode
    finOut->close();
  }
  _open = false;
}

// File_CI File_CI::openNextFile(uint8_t mode) {
//   // std::vector<std::string> fileNames;

//   return File_CI("dummy.txt", FILE_READ);
// }

char *File_CI::name() { return _fileName; }

File_CI::operator bool() { return File_Base::operator bool(); }

bool File_CI::isDirectory(void) { return File_Base::isDirectory(); }

} // namespace SDLib

#endif
