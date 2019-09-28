#ifndef BITFIELD_H
#define BITFIELD_H

#include <vector>
#include <string>

class BitField
{
    public:
        BitField(int bitCount);
        BitField(std::string str);
        virtual ~BitField(){};
        void operator << (int);
        void operator >> (int);
        BitField operator ^ (BitField);
        void SetByte(int, char);
        void ShiftInByte(char);
        BitField Left();
        BitField Right();
        std::string GetBytes() { return bytes; }
        std::string SetString(std::string newString) { bytes = newString; }
        int GetLength() { return bytes.length(); }

    protected:
        std::string bytes;
};

#endif // BITFIELD_H
