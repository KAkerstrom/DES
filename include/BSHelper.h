#ifndef BSHELPER_H
#define BSHELPER_H

#include <string>

class BSHelper
{
  public:
    //BSHelper();
    //virtual ~BSHelper();
    static std::string LeftCircularShift(std::string, int amount);
    static std::string Xor(std::string, std::string);
    static std::string Permute(std::string, int permTable[], int tableSize);
    static std::string AsciiToBits(std::string ascii);
    static std::string HexToBits(std::string hex);
    static std::string BitsToAscii(std::string bits);
};

#endif // BSHELPER_H
