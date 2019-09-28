#include "DES.h"
#include "Exceptions.h"
#include <vector>
#include <bitset>
#include <iostream>

DES::DES()
{

}

BitField DES::Encrypt(BitField data, BitField key)
{
  if(key.GetLength() != 8)
    throw DESException("Key must be 64 bits.");

  // Split the input data into 64-bit chunks
  std::vector<BitField> chunks;

  for(int i = 0; i < data.GetLength() % 8; i++)
  {
    // Break the data into 64 bit chunks
    BitField b(8);
    for(int j = 0; j < 8; j++)
    {
      if(data.GetLength() > i+j)
        b.SetByte(j, data.GetBytes()[i+j]);
      else
        b.SetByte(j, 0); // Pad the final chunk to be a full 64 bits
    }
    chunks.push_back(b);
  }

  // Initial Permutation
  chunks[0] = InitialPermutation(chunks[0]);

  // Generate keys
  std::vector<BitField> keys = GenerateKeys(key);

  std::string cipher;
  for(BitField b : chunks)
    for (int i = 0; i < 16; i++)
    {
      Round(data, keys[i]);
    }
}

BitField DES::Decrypt(BitField data, BitField key)
{

}

BitField DES::Round(BitField data, BitField key)
{

}

BitField DES::InitialPermutation(BitField data)
{
  std::string outputStr(data.GetBytes());
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
    {
      char permIndex = initPermTable[i*j];
      outputStr[i] = outputStr[i] | ((data.GetBytes()[permIndex / 8] >> permIndex % 8) & 1);
    }
  BitField output(outputStr);
  return output;
}

BitField DES::InverseInitialPermutation(BitField data)
{

}

BitField DES::Expansion(BitField data)
{

}

BitField DES::Substitution(BitField data)
{

}

BitField DES::PermutedChoice1(BitField key)
{

}

BitField DES::PermutedChoice2(BitField key)
{

}

std::vector<BitField> GenerateKeys(BitField key)
{
  // Drop every 8th bit to get 56-bit key
  std::string key56;
  for(int i = 0; i < 64; i += 8)
    key56 += key.GetBytes().substr(i, 7);
  BitField newKey(key56);

  // Permute the key
  int permChoice1[56]=
  {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
  };

  int permChoice2[48]=
  {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
  };

  std::string permKey(newKey.GetBytes());
  for(int i = 0; i < 56; i++)
      permKey[i] = permKey[i] | ((newKey.GetBytes()[permChoice1[i] / 8] >> permChoice1[i] % 8) & 1);
  newKey.SetString(permKey);

  std::vector<BitField> keys;
  int shifts[16]= { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
  for(int i = 0; i < 16; i++)
  {
    // Split into left and right
    BitField left = newKey.Left() << shifts[i];
    BitField right = newKey.Right() << shifts[i];
    BitField full(left.GetBytes() + right.GetBytes());
    std::string permKey2;
    for(int i = 0; i < 48; i++)
      permKey2[i] = permKey2[i] | ((newKey.GetBytes()[permChoice2[i] / 8] >> permChoice2[i] % 8) & 1);
    BitField addKey(permKey2);
    keys.push_back(addKey);
  }
  return keys;
}
