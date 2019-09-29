#include <iostream>
#include <bitset>
#include "Exceptions.h"
#include "BSHelper.h"
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
    //std::cin >> input;
    input = '1'; ////////////////////////
    std::string data;
    std::string key;
    if(input == "1")
    {
      std::cout << "\nInput data: ";
      //std::cin >> data;
      data = "abcdefghijklmnopqrstuvwxyz"; /////////////////////
      data = BSHelper::AsciiToBits(data);

      bool validKey = false;
      while (!validKey)
      {
        std::cout << "\nInput 64-bit hex string: [CHECK LENGTH]";
        //std::cin >> key;
        key = "1234567890123456"; //////////////////////
        if(key.length() != 16)
          std::cout << "\nInvalid key length. Must be 16 hex digits.";
        else
          try
          {
            key = BSHelper::HexToBits(key);
            validKey = true;
          }
          catch(ConversionException e)
          {
            std::cout << "\nInvalid key length. Must be 16 hex digits.";
          }
      }

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
