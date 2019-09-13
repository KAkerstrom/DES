#include "BitField.h"
#include <iostream>

/// Gets a 48-bit expansion of a 32 bit input
int Expansion(int input)
{
    return (input) | (input << 16);
}

int Substitution(int input)
{
    return input;
}

int Permutation(int input)
{
  return input;
}

int Round(int data, int key)
{
  int L = data >> 32;
  int R = data;
  int tmpR = Expansion(R);
  tmpR = Substitution(tmpR ^ key);
  R = Permutation(tmpR) ^ L;
  L = R;
  return (L << 32) | R;
}

int DES(int data, int key)
{
  for (int i = 0; i < 16; i++)
  {

  }
}

int main()
{
    BitField bf2 ("abcdef");

    BitField bf(6);
    bf.ShiftInByte(8);
    bf.ShiftInByte(1);
    bf.ShiftInByte(0);
    bf.ShiftInByte(0);
    bf.ShiftInByte('a');
    bf.ShiftInByte(1);

    bf2 = bf2 ^ bf;
    bf = bf ^ bf2;
    bf2 = bf2 ^ bf;

    for(int i = 0; i < bf2.GetLength(); i++)
        std::cout << +bf2.GetBytes()[i] << ' ';
}
