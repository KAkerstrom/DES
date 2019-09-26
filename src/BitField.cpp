#include "BitField.h"
#include "Exceptions.h"
#include<bits/stdc++.h>

BitField::BitField(int byteCount)
{
    bytes.resize(byteCount, 0);
}

BitField::BitField(std::string str)
{
    bytes = str;
}

void BitField::operator << (int amount)
{
    if(amount == 0)
        return;
    if(amount < 0)
        throw BitFieldException("Negative shifting not implemented.");
    if(amount > 8)
        throw BitFieldException("Shifting >8 bits not implemented.");

    char overflow = 0;
    for (int i = bytes.length() - 1; i >= 0; i--)
    {
        char byte = bytes[i];
        bytes[i] <<= amount;
        bytes[i] |= overflow;
        overflow = ((unsigned char)byte) >> (8 - amount);
    }
    bytes[bytes.length() - 1] |= overflow;
}

void BitField::operator >> (int amount)
{
    if(amount == 0)
        return;
    if(amount < 0)
        throw BitFieldException("Negative shifting not implemented.");
    if(amount > 8)
        throw BitFieldException("Shifting >8 bits not implemented.");

    char overflow = 0;
    for (int i = 0; i < bytes.length(); i++)
    {
        char byte = bytes[i];
        bytes[i] >>= amount;
        bytes[i] |= overflow;
        overflow = byte << (8 - amount);
    }
    bytes[0] |= overflow;
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

BitField BitField::operator ^ (BitField bf)
{
    if(bf.GetLength() != bytes.length())
        throw BitFieldException("BitFields must be the same size for XOR.");
    BitField output(bytes.length());
    for (int i = 0; i < bytes.length(); i++)
        output.SetByte(i, bytes[i] ^ bf.GetBytes()[i]);
    return output;
}

BitField BitField::Left()
{
    if(GetLength() % 2 != 0)
        throw BitFieldException("BitField cannot be evenly split.");
    BitField output(bytes.substr(0, bytes.length() / 2));
    return output;
}

BitField BitField::Right()
{
    if(GetLength() % 2 != 0)
        throw BitFieldException("BitField cannot be evenly split.");
    BitField output(bytes.substr(bytes.length() / 2));
    return output;
}
