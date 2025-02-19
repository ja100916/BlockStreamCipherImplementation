#ifndef CIPHER_CONFIG_H
#define CIPHER_CONFIG_H

#include <cstddef>
#include <string>

namespace cipher {
    // Configuration constants
    struct Config {
        static const size_t BLOCK_SIZE = 16;           // Default block size
        static const char PADDING_BYTE = 0x81;         // Padding byte value
        static const size_t MAX_KEY_SIZE = 1024;       // Maximum key size
        static const size_t BUFFER_SIZE = 8192;        // File read buffer size
        
        // Error messages
        static const std::string ERR_INVALID_FUNCTION;
        static const std::string ERR_INVALID_MODE;
        static const std::string ERR_KEY_NOT_FOUND;
        static const std::string ERR_INPUT_NOT_FOUND;
        static const std::string ERR_KEY_TOO_LARGE;
    };
}

#endif