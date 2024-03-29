#ifndef BSHELPER_H
#define BSHELPER_H

#include <string>

class BSHelper
{
  public:
    static std::string LeftCircularShift(std::string, int amount);
    static std::string Xor(std::string, std::string);
    static std::string Permute(std::string, char permTable[], int tableSize);
    static std::string AsciiToBits(std::string ascii);
    static std::string HexToBits(std::string hex);
    static std::string BitsToAscii(std::string bits);
    static std::string BitsToHex(std::string bits);
};

#endif // BSHELPER_H
