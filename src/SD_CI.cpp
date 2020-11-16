#include "SD_CI.h"
#ifdef ARDUINO_CI

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

namespace SDLib {

File_CI File_CI::openNextFile(uint8_t mode) { File_Base::openNextFile(mode); }

void File_CI::rewindDirectory(void) { File_Base::rewindDirectory(); }

// =================================================================

bool SDClass_CI::begin(uint8_t csPin) { SDClass_Base::begin(csPin); }

bool SDClass_CI::begin(uint32_t clock, uint8_t csPin) {
  SDClass_Base::begin(clock, csPin);
}

void SDClass_CI::end() { SDClass_Base::end(); }

File_CI SDClass_CI::open(const char *filename, uint8_t mode) {
  SDClass_Base::open(filename, mode);
}

bool SDClass_CI::exists(const char *filepath) {
  SDClass_Base::exists(filepath);
}

bool SDClass_CI::mkdir(const char *filepath) { SDClass_Base::mkdir(filepath); }

bool SDClass_CI::remove(const char *filepath) {
  SDClass_Base::remove(filepath);
}

bool SDClass_CI::rmdir(const char *filepath) { SDClass_Base::rmdir(filepath); }

} // namespace SDLib

#endif
