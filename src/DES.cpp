#include "DES.h"
#include "Exceptions.h"

DES::DES()
{

}

BitField DES::Encrypt(BitField data, BitField key)
{
  if(key.GetLength() != 8)
    throw DESException("Key must be 64 bits.");


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
