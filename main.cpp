#define DEBUG

#include <iostream>
#include <bitset>
#include "Exceptions.h"
#include "BSHelper.h"
#include "DES.h"
#include "test.h"


int main(int argc, char** argv)
{
  DES des;

  std::cout << "Welcome. Press a key...\n\n1- Encrypt\n2- Decrypt\n3- Encrypt / Decrypt\n";

  std::string input;
  while (input != "1" && input != "2" && input != "3")
  {
    std::cin >> input;
    std::string data;
    std::string key;
    if(input == "1")
    {
      std::cout << "\nInput data: ";

      #ifdef DEBUG
        data = BSHelper::HexToBits("0123456789ABCDEF");
      #else
        std::cin >> data;
        data = BSHelper::AsciiToBits(data);
      #endif // DEBUG


      bool validKey = false;
      while (!validKey)
      {
        std::cout << "\nInput 64-bit hex key: ";

        #ifdef DEBUG
          key = "133457799BBCDFF1";
        #else
          std::cin >> key;
        #endif // DEBUG

        if(key.length() != 16)
          std::cout << "\nInvalid key length. Must be 16 hex digits.";
        else
          try
          {
            key = BSHelper::HexToBits(key);
            #ifdef DEBUG
            std::cout << "\n\nKey Binary: \n" << key << '\n';
            #endif // DEBUG

            validKey = true;
          }
          catch(ConversionException e)
          {
            std::cout << "\nInvalid key length. Must be 16 hex digits.";
          }
      }

      std::string output = des.Encrypt(data, key);
      std::cout << BSHelper::BitsToHex(output);
    }
    else if (input == "2")
    {
      std::cout << "\nInput cipher hex: ";

      std::cin >> data;
      data = BSHelper::HexToBits(data);

      bool validKey = false;
      while (!validKey)
      {
        std::cout << "\nInput 64-bit hex key: ";

        #ifdef DEBUG
          key = "133457799BBCDFF1";
        #else
          std::cin >> key;
        #endif // DEBUG

        if(key.length() != 16)
          std::cout << "\nInvalid key length. Must be 16 hex digits.";
        else
          try
          {
            key = BSHelper::HexToBits(key);
            #ifdef DEBUG
            std::cout << "\n\nKey Binary: \n" << key << '\n';
            #endif // DEBUG

            validKey = true;
          }
          catch(ConversionException e)
          {
            std::cout << "\nInvalid key length. Must be 16 hex digits.";
          }
      }

      std::string output = des.Decrypt(data, key);
      std::cout << output;
    }
    else if (input == "3")
    {
      std::cout << "\nInput data: ";

      std::cin >> data;
      data = BSHelper::AsciiToBits(data);


      bool validKey = false;
      while (!validKey)
      {
        std::cout << "\nInput 64-bit hex key: ";

        #ifdef DEBUG
          key = "133457799BBCDFF1";
        #else
          std::cin >> key;
        #endif // DEBUG

        if(key.length() != 16)
          std::cout << "\nInvalid key length. Must be 16 hex digits.";
        else
          try
          {
            key = BSHelper::HexToBits(key);
            #ifdef DEBUG
            std::cout << "\n\nKey Binary: \n" << key << '\n';
            #endif // DEBUG

            validKey = true;
          }
          catch(ConversionException e)
          {
            std::cout << "\nInvalid key length. Must be 16 hex digits.";
          }
      }

      std::string output = des.Encrypt(data, key);
      std::cout << "\n\nENCRYPTED: " << (output) << '\n';
      output = des.Decrypt(output, key);
      std::cout << "RESULT:    " << BSHelper::BitsToAscii(output) << "\n\n";
    }
    else
      std::cout << "\n\nInvalid input.\n1- Encrypt\n2- Decrypt\n";
  }
}
