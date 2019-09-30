//#define DEBUG

#include <iostream>
#include <bitset>
#include <fstream>
#include "Exceptions.h"
#include "BSHelper.h"
#include "DES.h"
#include "test.h"


std::string GetData()
{
  bool validFile = false;
  std::string path;
  while (!validFile)
  {
    std::cout << "\nInput file name: ";
    std::cin >> path;
//    for(int i = 0; i < path.length(); i++)
//      if(path[i] == '.')
//      {
//        path = path.substr(0, i);
//        break;
//      }
    path = "files/" + path;

    try
    {
      std::ifstream file;
      file.open(path.c_str());
      std::string output;
      if (file.is_open())
        while (!file.eof())
          file >> output;
      file.close();
      validFile = true;
    }
    catch(const std::exception& e)
    {
      std::cout << "\n\nCould not read from file.\n";
      std::cout << "Only enter the filename (with the extension), such as \"file.txt\".\n";
      std::cout << "The file should be located in the \"files\" directory, found in the same location as the EXE.\n";
    }
  }

  std::vector<std::string> options;
  options.push_back("1");
  options.push_back("2");
  std::string selection = GetSelection("What is the file encoding?\n1- ASCII\n2- Hexadecimal", options);

  if(selection == "1")
    return BSHelper::AsciiToBits(data);
  return BSHelper::HexToBits(data);
}

std::string GetKey()
{
  bool validKey = false;
  std::string key;
  while (!validKey)
  {
    std::cout << "\nInput 16-digit hex key: ";
    std::cin >> key;

    if(key.length() != 16)
      std::cout << "\nInvalid key length. Must be 16 hex digits.";
    else
    {
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
        std::cout << "\nInvalid key input / length. Must be 16 hex digits.";
      }
    }
  }
}

std::string GetSelection(std::string menu, std::vector<std::string> options)
{
  bool validOption = false;
  std::string selection;
  while (!validOption)
  {
    std::cout << "\n" << menu;
    std::cout << "\nYour selection: ";
    std::cin >> selection;
    std::cout << "\n\n";

    for(int i = 0; i < options.size(); i++)
      if(selection == options[i])
        validOption = true;
    if(!validOption)
      std::cout << "Invalid option selected.\n";
  }
  return selection;
}


int main(int argc, char** argv)
{
  DES des;

  std::cout << " _____  _______ ______\n|     \\|    ___|    __|\n|  --  |    ___|__    |\n|_____/|_______|______|\nENCRYPTION & DECRYPTION\n\n";
  std::cout << "CPSC 3730  CRYPTOGRAPHY\n";
  std::cout << "PROGRAMMING  ASSIGNMENT\n";
  std::cout << "   BY KYLE AKERSTROM\n\n";

  std::vector<std::string> options;
  options.push_back("1");
  options.push_back("2");
  options.push_back("3");
  std::string input = GetSelection("1- Encrypt\n2- Decrypt\n3- Encrypt & Decrypt (Test)", options);

  if(input == "1")
  {
    std::string data = GetData();
    std::string key = GetKey();
    std::string output = des.Encrypt(data, key);
    std::cout << BSHelper::BitsToHex(output); //TODO output to file
  }
  else if (input == "2")
  {
    std::string data = GetData();
    std::string key = GetKey();
    std::string output = des.Decrypt(data, key);
    std::cout << output;
  }
  else if (input == "3")
  {
    std::cout << "\nInput ASCII data (with no spaces): ";
    std::string data;
    std::cin >> data;
    std::string key = GetKey();
    std::string output = des.Encrypt(data, key);
    std::cout << "\n\nENCRYPTED: " << BSHelper::BitsToHex(output) << '\n';
    output = des.Decrypt(output, key);
    std::cout << "RESULT:    " << BSHelper::BitsToAscii(output) << "\n\n";
  }

}
