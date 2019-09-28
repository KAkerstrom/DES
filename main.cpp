#include "BitField.h"
#include <iostream>
#include <bitset>
#include "DES.h"
#include "test.h"

int main(int argc, char** argv)
{
  if(argv[1] == "test");


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

      std::string output = des.Encrypt(data, key);
      std::cout << output;
    }
    else if (input == "2")
    {

    }
    else
      std::cout << "\n\nInvalid input.\n1- Encrypt\n2- Decrypt\n";
  }
}
