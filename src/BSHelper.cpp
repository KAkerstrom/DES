#include "BSHelper.h"
#include "Exceptions.h"
#include <bitset>
#include <sstream>

std::string BSHelper::LeftCircularShift(std::string input, int amount)
{

  return input.substr(amount + 1) + input.substr(0, amount);
}

std::string BSHelper::Xor(std::string str1, std::string str2)
{
  std::string output(str1.length(), 0);
  for (int i = 0; i < str1.length(); i++)
    output[i] = (str1[i] == '1') ^ (str2[i] == '1') ? '1' : '0';
  return output;
}

std::string BSHelper::Permute(std::string input, char permTable[], int tableSize)
{
  std::string output(tableSize, 0);
  for(int i = 0; i < tableSize; i++)
    output[i] = input[permTable[i]];
  return output;
}

std::string BSHelper::AsciiToBits(std::string ascii)
{
  std::stringstream ssOutput;
  for(int i = 0; i < ascii.length(); i++)
  {
    std::bitset<8> bs(ascii[i]);
    ssOutput << bs.to_string();
  }

  std::string output;
  ssOutput >> output;
  return output;
}

std::string BSHelper::HexToBits(std::string hex)
{
  std::string output(hex.length() * 4, 0);
  unsigned char bits;
  for(int i = 0; i < hex.length(); i++)
  {
    if(hex[i] >= '0' && hex[i] <= '9')
      bits = hex[i] - '0';
    else if (hex[i] >= 'A' && hex[i] <= 'F')
      bits = hex[i] - 'A' + 10;
    else if (hex[i] >= 'a' && hex[i] <= 'f')
      bits = hex[i] - 'a' + 10;
    else
      throw new ConversionException("Invalid hex input.");

    for(int j = 0; j < 4; j++)
      output[i * j] = (bits >> 4 - j) & 1 ? '1' : '0';
  }
  return output;
}

std::string BSHelper::BitsToAscii(std::string bits)
{
  std::string output(bits.length() / 8, 0);
  for(int i = 0; i < bits.length() / 8; i++)
  {
    std::bitset<8> bs(bits.substr(i * 8, 8));
    output[i] = (unsigned char)bs.to_ulong();
  }
  return output;
}












