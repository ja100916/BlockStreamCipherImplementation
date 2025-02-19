#include "stream.h"
#include <fstream>
#include <stdexcept>
#include <iostream>


void StreamCipher::process() {
    std::ifstream input(inputPath, std::ios::binary); //open input file
    if (!input.is_open()) {
        throw std::runtime_error("Input File does not exist");
    }

    std::ofstream output(outputPath, std::ios::binary); //open output file
    char c;
    size_t keyIndex = 0; //track current key position

    while (input.get(c)) {
        if (keyIndex >= key.size()) { //process byte by byte
            keyIndex = 0; // wrap key if needed
        }
        char processed = c ^ key[keyIndex]; //xor with key byte
        output.put(processed);
        keyIndex;
    }
}
