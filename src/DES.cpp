#include "DES.h"
#include "Exceptions.h"
#include <vector>
#include <bitset>

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

  std::string cipher;
  for(BitField b : chunks)
    for (int i = 0; i < 16; i++)
    {
      Round(data, key);
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
