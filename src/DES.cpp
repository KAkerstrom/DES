#include "DES.h"

DES::DES()
{

}

BitField DES::Encrypt(BitField data, BitField key)
{

}

BitField DES::Decrypt(BitField data, BitField key)
{

}

BitField BitField::Round(BitField data, BitField key);
BitField BitField::InitialPermutation(BitField data);
BitField BitField::InverseInitialPermutation(BitField data);
BitField BitField::Expansion(BitField data);
BitField BitField::Substitution(BitField data);
BitField BitField::PermutedChoice1(BitField key);
BitField BitField::PermutedChoice2(BitField key);
