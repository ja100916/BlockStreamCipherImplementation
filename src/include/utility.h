#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "cipher_config.h"

namespace cipher {
    class CipherBase {
    protected:
        std::string inputPath;                         // Input file path
        std::string outputPath;                        // Output file path
        std::string keyPath;                          // Key file path
        bool isEncryption;                            // Operation mode
        std::vector<char> key;                        // Key storage
        std::vector<char> buffer;                     // Processing buffer

        void readKey();                               // Read key from file
        void validateKey() const;                     // Validate key properties
        void initializeBuffer();                      // Initialize processing buffer

    public:
        CipherBase(const std::string& input, 
                  const std::string& output,
                  const std::string& keyfile, 
                  bool encrypt);
        
        virtual void process() = 0;                   // Process data
        virtual ~CipherBase() = default;

        // Added utility methods
        static bool isFileExists(const std::string& path);
        static std::string getFileExtension(const std::string& path);
        static size_t getFileSize(const std::string& path);
    };
}

#endif