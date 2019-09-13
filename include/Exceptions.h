#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class BitFieldException: public std::runtime_error {
 public:
  explicit BitFieldException(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif // EXCEPTIONS_H
