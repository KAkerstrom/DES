#ifndef BITFIELD_H
#define BITFIELD_H

#include <vector>
#include <string>

class BitField
{
    public:
        BitField(int bitCount);
        virtual ~BitField(){};
        void operator << (int);
        void operator >> (int);
        void operator ^ (BitField);
        void SetByte(int, char);
        void ShiftInByte(char);
        std::string GetBytes() { return bytes; }
        int GetLength() { return bytes.length(); }

    protected:
        std::string bytes;
};

#endif // BITFIELD_H
