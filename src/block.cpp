#include "block.h"
#include <fstream>
#include <stdexcept>

//padding to incomplete block
std::vector<char> BlockCipher::padBlock(const std::vector<char>&block) {
    std::vector<char> padded = block;
    while (padded.size() < BLOCK_SIZE) { //add puadding until bloxk size
        padded.push_back(PADDING_BYTE);
    }
    return padded;
}

//xor block with key
std::vector<char> BlockCipher::xorBlock(const std::vector<char>& block) {
    std::vector<char> result(BLOCK_SIZE);
    for (size_t i = 0; i < BLOCK_SIZE; i++) { //XOR each byte
        result[i] = block[i] ^ key[i];
    }
    return result;
}

//swap bytes based on key values
std::vector<char> BlockCipher::swapBytes(std::vector<char> block) {
    size_t start = 0; //start of block
    size_t end = BLOCK_SIZE - 1; //end of block
    size_t keyIndex = 0; //current key position

    while (start < end) {
        if (keyIndex >= key.size()) { //wraps key if needed
            keyIndex = 0;
        }

        if (key[keyIndex] % 2 == 1) { //swaps if key byte is oodd
            std::swap(block[start], block[end]);
            end--;
        }
        start++;
        keyIndex++;
    }
    return block;
}

//Remove padding buytes
void BlockCipher::removePadding(std::vector<char>& block) {
    while (!block.empty() && block.back() == PADDING_BYTE) { //remove padding bytes
        block.pop_back();
    }
}

void BlockCipher::process() {
    std::ifstream input(inputPath, std::ios::binary); //open input file
    if (!input.is_open()) {
        throw std::runtime_error("Input file does not exist");
    }

    std::ofstream output(outputPath, std::ios::binary); //open output file
    std::vector<char> block;
    char c;

    if (isEncryption) {
        //encryption proces: pad > xor > swap
        while (input.get(c)) { //read input byte
            block.push_back(c);
            if (block.size() == BLOCK_SIZE) { //process full block
                auto processed = swapBytes(xorBlock(block));
                output.write(processed.data(), processed.size());
                block.clear();
            } 
        }

        if (!block.empty()) { //handle final partial block
            auto padded = padBlock(block);
            auto processed = swapBytes(xorBlock(padded));
            output.write(processed.data(), processed.size());
        }
    } else {
        //decyrption process: swap > xor > remove padding
        while (input.get(c)) { //read input byte
            block.push_back(c);
            if (block.size() == BLOCK_SIZE) { //process full block
            auto processed = xorBlock(swapBytes(block));
            if (!input.peek()) { //if last block remove padding
                removePadding(processed);
            }
            output.write(processed.data(), processed.size());
            block.clear();
            }
        }
    }
}