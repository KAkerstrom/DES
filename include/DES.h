#ifndef DES_H
#define DES_H

#include "BitField.h"

class DES
{
    public:
        DES();
        virtual ~DES(){};
        BitField Encrypt(BitField data, BitField key);
        BitField Decrypt(BitField data, BitField key);

    private:

};

#endif // DES_H
