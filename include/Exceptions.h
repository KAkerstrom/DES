#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class DESException: public std::runtime_error {
 public:
  explicit DESException(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

class ConversionException: public std::runtime_error {
 public:
  explicit ConversionException(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif // EXCEPTIONS_H
