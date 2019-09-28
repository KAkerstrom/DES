#include "BSHelper.h"
#include <bitset>
//BSHelper::BSHelper()
//{
//  //ctor
//}
//
//BSHelper::~BSHelper()
//{
//  //dtor
//}

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

std::string BSHelper::Permute(std::string input, int permTable[], int tableSize)
{
  std::string output(tableSize, 0);
  for(int i = 0; i < tableSize; i++)
    output[i] = input[permTable[i]];
  return output;
}

std::string AsciiToBits(std::string ascii)
{
  std::string output(ascii.length() * 8, 0);
  for(int i = 0; i < ascii.length(); i++)
    for(int j = 0; j < 8; j++)
      output[i * j] = (unsigned char)(ascii[j] >> j) & 1 ? '1' : '0';
  return output;
}

std::string HexToBits(std::string hex)
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

    for(int j = 0; j < 4; j++)
      output[i * j] = (bits >> 4 - j) & 1 ? '1' : '0';
  }
  return output;
}

std::string BitsToAscii(std::string bits)
{
  std::string output(bits.length() / 8, 0);
  for(int i = 0; i < bits.length() / 8; i++)
  {
    std::bitset<8> bs(bits.substr(i * 8, 8));
    output[i] = (unsigned char)bs.to_ulong();
  }
  return output;
}












