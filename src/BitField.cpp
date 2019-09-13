#include "BitField.h"
#include "Exceptions.h"

BitField::BitField(int byteCount)
{
    bytes.resize(byteCount, 0);
}

void BitField::operator << (int amount)
{
    if(amount > 8)
        throw BitFieldException("Cannot currently shift more than 8 bits.");

    char overflow = 0;
    for (int i = bytes.length(); i >= 0; i--)
    {
        char byte = bytes[i];
        bytes[i] <<= amount;
        bytes[i] |= overflow;
        overflow = byte >> (8 - amount);
    }
    bytes[bytes.length()] |= overflow;
}

void BitField::operator >> (int amount)
{
    if(amount > 8)
        throw BitFieldException("Cannot currently shift more than 8 bits.");

    char overflow = 0;
    for (int i = 0; i < bytes.length(); i++)
    {
        char byte = bytes[i];
        bytes[i] >>= amount;
        bytes[i] |= overflow;
        overflow = byte << (8 - amount);
    }
    bytes[bytes.length()] |= overflow;
}

void BitField::SetByte(int byteIndex, char data)
{
    if(byteIndex >= bytes.length() || byteIndex < 0)
        throw BitFieldException("Byte index out of bounds.");
    bytes[byteIndex] = data;
}

void BitField::ShiftInByte(char newByte)
{
    for (int i = 0; i < bytes.length(); i++)
        bytes[i] = bytes[i + 1];
    bytes[bytes.length() - 1] = newByte;
}

void BitField::operator ^ (BitField bf)
{
    if(bf.GetLength() != bytes.length())
        throw BitFieldException("BitFields must be the same size for XOR.");
}
