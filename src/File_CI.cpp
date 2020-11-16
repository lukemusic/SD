#include "SD_CI.h"
#ifdef ARDUINO_CI

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

namespace SDLib {

File_CI::File_CI(SdFile f, const char *name) : File_Base(f, name) {}

File_CI::File_CI(void) : File_Base() {}

size_t File_CI::write(uint8_t value) { return File_Base::write(value); }

size_t File_CI::write(const uint8_t *buf, size_t size) {
  return File_Base::write(buf, size);
} // namespace SDLib

int File_CI::availableForWrite() { return File_Base::availableForWrite(); }

int File_CI::read() { return File_Base::read(); }

int File_CI::peek() { return File_Base::peek(); }

int File_CI::available() { return File_Base::available(); }

void File_CI::flush() { return File_Base::flush(); }

int File_CI::read(void *buf, uint16_t nbyte) { return File_Base::read(buf, nbyte); }

bool File_CI::seek(uint32_t pos) { return File_Base::seek(pos); }

uint32_t File_CI::position() { return File_Base::position(); }

uint32_t File_CI::size() { return File_Base::size(); }

void File_CI::close() { return File_Base::close(); }

File_CI::operator bool() { return File_Base::operator bool(); }

char *File_CI::name() { return File_Base::name(); }

bool File_CI::isDirectory(void) { return File_Base::isDirectory(); }

} // namespace SDLib

#endif
