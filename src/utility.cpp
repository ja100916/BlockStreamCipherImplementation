#include "utility.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace cipher {
    // Initialize static error messages
    const std::string Config::ERR_INVALID_FUNCTION = "Invalid Function Type";
    const std::string Config::ERR_INVALID_MODE = "Invalid Mode Type";
    const std::string Config::ERR_KEY_NOT_FOUND = "Key File Does Not Exist";
    const std::string Config::ERR_INPUT_NOT_FOUND = "Input File Does Not Exist";
    const std::string Config::ERR_KEY_TOO_LARGE = "Key File Too Large";

    CipherBase::CipherBase(const std::string& input, 
                          const std::string& output,
                          const std::string& keyfile, 
                          bool encrypt)
        : inputPath(input), outputPath(output), 
          keyPath(keyfile), isEncryption(encrypt) {
        
        initializeBuffer();                           // Initialize processing buffer
        readKey();                                    // Read and validate key
        validateKey();                                // Validate key properties
    }

    void CipherBase::readKey() {
        if (!isFileExists(keyPath)) {
            throw std::runtime_error(Config::ERR_KEY_NOT_FOUND);
        }

        if (getFileSize(keyPath) > Config::MAX_KEY_SIZE) {
            throw std::runtime_error(Config::ERR_KEY_TOO_LARGE);
        }

        std::ifstream keyFile(keyPath, std::ios::binary);
        char c;
        while (keyFile.get(c)) {
            key.push_back(c);
        }
    }

    void CipherBase::validateKey() const {
        // Add key validation logic here
        if (key.empty()) {
            throw std::runtime_error("Empty key file");
        }
    }

    void CipherBase::initializeBuffer() {
        buffer.reserve(Config::BUFFER_SIZE);          // Pre-allocate buffer
    }

    bool CipherBase::isFileExists(const std::string& path) {
        return std::filesystem::exists(path);
    }

    std::string CipherBase::getFileExtension(const std::string& path) {
        return std::filesystem::path(path).extension().string();
    }

    size_t CipherBase::getFileSize(const std::string& path) {
        return std::filesystem::file_size(path);
    }
}