#ifndef BLOCK_H
#define BLOCK_H

#include "utility.h"

class BlockCipher : public CipherBase {
private:
    static const size_t BLOCK_SIZE = 16; //fixed block size
    static const char PADDING_BYTE = 0x81; //padding value

    std::vector<char> padBlock(const std::vector<char>& block); //adds padding
    std::vector<char> xorBlock(const std::vector<char>& block); //xor with key
    std::vector<char> swapBytes(std::vector<char> block); //swap based on key
    void removePadding(std::vector<char>& block); //remove padding

public:
    using CipherBase::CipherBase; //inherit constructor
    void process() override;  
};

#endif