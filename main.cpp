#include "BitField.h"
#include <iostream>
#include <bitset>
#include "DES.h"

int main()
{
  DES des;

  std::cout << "Welcome. Press a key...\n\n1- Encrypt\n2- Decrypt\n";

  std::string input;
  while (input != "1" && input != "2")
  {
    std::cin >> input;
    std::string data;
    std::string key;
    if(input == "1")
    {
      std::cout << "\nInput data: ";
      std::cin >> data;
      std::cout << "\nInput 64-bit hex string: [CHECK LENGTH]";
      std::cin >> key;

      BitField dataBits(data);
      BitField keyBits(key);
      BitField output = des.Encrypt(dataBits, keyBits);
    }
    else if (input == "2")
    {

    }
    else
      std::cout << "\n\nInvalid input.\n1- Encrypt\n2- Decrypt\n";
  }
}
