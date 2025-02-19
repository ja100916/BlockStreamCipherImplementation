#include "catch2/catch.hpp"
#include "block.h"
#include <fstream>

TEST_CASE("Block Cipher Encryption", "[block]") {
    // Setup test files
    std::string testInput = "test_input.txt";
    std::string testOutput = "test_output.bin";
    std::string testKey = "test_key.txt";
    
    SECTION("Basic encryption") {
        // Create test input
        std::ofstream input(testInput);
        input << "Hello, World!";
        input.close();

        // Create test key
        std::ofstream key(testKey);
        key << "TESTKEY1234567890";
        key.close();

        // Test encryption
        cipher::BlockCipher cipher(testInput, testOutput, testKey, true);
        REQUIRE_NOTHROWS(cipher.process());
        
        // Verify output exists and is not empty
        REQUIRE(std::filesystem::exists(testOutput));
        REQUIRE(std::filesystem::file_size(testOutput) > 0);
    }

    // Clean up test files
    std::filesystem::remove(testInput);
    std::filesystem::remove(testOutput);
    std::filesystem::remove(testKey);
}
