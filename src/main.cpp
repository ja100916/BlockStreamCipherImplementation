#include <iostream>
#include <memory>
#include "block.h"
#include "stream.h"
#include "utility.h"

int main (int argc, char* argv[]) {
    try {
        if (argc != 6) { //validate args
            return 1;
        }

        //parse cmd line arsg
        std::string cipherType = argv[1]; //b for block s for stream
        std::string inputPath = argv[2]; //input file path
        std::string outputPath = argv[3]; //output file path
        std::string keyPath = argv[4]; //key file path
        std::string mode = argv[5]; // e encrypt, d decrypt

        //validate cipher type
        if (cipherType != "B" && cipherType != "S") {
            std::cerr << "Invalid Function Type" << std::endl;
            return 1;
        }

        //validate operatino mode
        if (mode != "E" && mode != "D") {
            std::cerr << "Invalid Mode Type" << std::endl;
            return 1;
        }

        bool isEncryption = (mode == "E"); //convert mode to bool
        std::unique_ptr<CipherBase> cipher; //polymorphic cipher pointa

        //create cipher instance
        if (cipherType == "B") {
            cipher = std::make_unique<BlockCipher>(inputPath, outputPath, keyPath, isEncryption);
        } else {
            cipher = std::make_unique<StreamCipher>(inputPath, outputPath, keyPath, isEncryption);
        }

        cipher->process(); //exe encrypt/decrypt
        return 0;

    } catch (const std::runtime_error& e) { //handle file + key errs
        std::cerr << e.what() << std::endl;
        return 1;
    }
}