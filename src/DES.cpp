#define DEBUG

#include "DES.h"
#include "Exceptions.h"
#include "BSHelper.h"
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

DES::DES()
{
}

/// Encrypt the data with the key
/// data: The data as a binary string
/// key: The key as a binary string
/// returns the encrypted data as a binary string
std::string DES::Encrypt(std::string data, std::string key)
{
  // Split the input data into 64-bit chunks
  std::vector<std::string> chunks;

  #ifdef DEBUG
  std::cout << "\n\ndata: \n" << data << "\n\n";
  #endif // DEBUG

  int index = 0;
  do
  {
    std::string chunk;
    if(index + 64 < data.length())
      chunk = data.substr(index * 64, 64);
    else
      chunk = data.substr(index);
    if(chunk.length() < 64)
      chunk += std::string(64 - chunk.length(), '0');
    chunks.push_back(chunk);

  }
  while (index++ < data.length() / 64);

  #ifdef DEBUG
  std::cout << "Chunks: \n";
  for(int i = 0; i < chunks.size(); i++)
    std::cout << chunks[i] + '\n';
  #endif

  // Initial Permutation
  chunks[0] = BSHelper::Permute(chunks[0], initPermTable, 64);

  #ifdef DEBUG
  std::cout << "\n" << "After permutation: \n" << data << "\n\n";
  #endif // DEBUG

  // Generate keys
  std::vector<std::string> keys = GenerateKeys(key);

  #ifdef DEBUG
  std::cout << "\n\nKeys:\n";
  for (int i = 0; i < keys.size(); i++)
    std::cout << keys[i] << '\n';
  #endif // DEBUG

  std::stringstream cipherStream;
  for(int i = 0; i < chunks.size(); i++)
  {
    #ifdef DEBUG
    std::cout << "\n-----------------\nChunk " << i << "\n-----------------\n\n";
    #endif // DEBUG
    std::string cipherChunk = chunks[i];
    for (int j = 0; j < 16; j++)
    {
      #ifdef DEBUG
      std::cout << "\nRound " << j << ":";
      #endif // DEBUG
      cipherChunk = Round(cipherChunk, keys[j]);
    }

    // 32 bit swap
    cipherChunk = cipherChunk.substr(cipherChunk.length() + 1) + cipherChunk.substr(0, cipherChunk.length() / 2);

    // Inverse initial permutation
    cipherChunk = BSHelper::Permute(cipherChunk, inversePermTable, 64);

    cipherStream << cipherChunk;
  }

  std::string output;
  cipherStream >> output;
  return output;
}

/// Decrypt the data with the key
/// data: The data as a binary string
/// key: The key as a binary string
/// returns the decrypted ascii plain-text
std::string DES::Decrypt(std::string data, std::string key)
{

}

/// Perform a single round of the DES algorithm
/// data: The round data as a binary string
/// key: The round key as a binary string
/// returns the a string containing the left and right halves for the round joined together
std::string DES::Round(std::string data, std::string key)
{
  std::string left = data.substr(0, data.length() / 2);
  std::string right = data.substr(data.length() / 2);
  std::string originalRight = right;
  char expansionTable[48]=
  {
    32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
    12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
    22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1
  };
  right = BSHelper::Permute(right, expansionTable, 48);
      #ifdef DEBUG
      std::cout << "\nExpansion: " << right;
      std::cout << "\nKey:       " << key;
      #endif // DEBUG
  right = BSHelper::Xor(right, key);
      #ifdef DEBUG
      std::cout << "\nExpXorKey: " << right;
      #endif // DEBUG
  right = Substitution(right);
      #ifdef DEBUG
      std::cout << "\nSBoxes:    " << right;
      #endif // DEBUG
  char permute[32]=
  {
    16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
  };
  right = BSHelper::Permute(right, permute, 32);
      #ifdef DEBUG
      std::cout << "\nf(R,K):   " << right;
      std::cout << "\nL = R-1:  " << originalRight << "\n\n";
      #endif // DEBUG
  right = BSHelper::Xor(left, right);
  return originalRight + right;
}

/// Substitute the input data using the Substitution Tables
/// data: The data as a binary string
/// returns the substituted data as a binary string
std::string DES::Substitution(std::string data)
{
  // Break data into S-Box inputs
  std::vector<std::string> inputs;
  for(int i = 0; i < 48; i += 6)
  {
    std::string input = data.substr(i, 6);
    inputs.push_back(input);
  }

  std::stringstream ssOutput;
  for(int i = 0; i < 8; i++)
  {
    std::string rowStr("");
    rowStr += inputs[i][0] + inputs[i][inputs[i].length() - 1];
    std::string colStr("");
    colStr += inputs[i].substr(1, inputs[i].length() - 2);

    std::bitset<2> rowBits(rowStr); // THIS DOESN'T WORK. DEBUG UP TO THIS POINT TO ENSURE GOOD INPUT ////////////////////////
    std::bitset<4> colBits(colStr);
    char row = (unsigned char)rowBits.to_ulong();
    char col = (unsigned char)colBits.to_ulong();

    std::bitset<8> subBits(sTables[i][row][col]);
    ssOutput << subBits.to_string();
  }
  std::string output;
  ssOutput >> output;
  return output;
}

/// Generate the 16 round keys
/// key: The provided key as a binary string
/// returns a vector of keys
std::vector<std::string> DES::GenerateKeys(std::string key)
{
  // Drop every 8th bit to get 56-bit key
  std::string newKey;
  for(int i = 0; i < 64; i += 8)
    newKey += key.substr(i, 7);

  // Permute the key
  char permChoice1[56]=
  {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4
  };

  char permChoice2[48]=
  {
    14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,
    52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
  };

  newKey = BSHelper::Permute(key, permChoice1, 56);

  std::vector<std::string> keys;
  int shifts[16]= { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
  for(int i = 0; i < 16; i++)
  {
    // Split into left and right
    std::string left = BSHelper::LeftCircularShift(newKey.substr(0, newKey.length() / 2), shifts[i]);
    std::string right = BSHelper::LeftCircularShift(newKey.substr(newKey.length() / 2), shifts[i]);
    newKey = left + right;
    keys.push_back(BSHelper::Permute(newKey, permChoice2, 48));
  }
  return keys;
}
