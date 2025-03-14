#include "encryption/aes.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string>
#include <vector>

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

// Measure encryption time for multiple blocks
double measureBatchEncryptionTime(AESCipher &aes,
                                const std::vector<std::vector<unsigned char>> &blocks,
                                std::vector<std::vector<unsigned char>> &encrypted) {
    auto start = std::chrono::high_resolution_clock::now();
    
    VL_VIRTUALIZATION_BEGIN;
    encrypted.resize(blocks.size());
    for (size_t i = 0; i < blocks.size(); ++i) {
        encrypted[i] = aes.encrypt(blocks[i]);
    }
    VL_VIRTUALIZATION_END;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

// Measure decryption time for multiple blocks
double measureBatchDecryptionTime(AESCipher &aes,
                                const std::vector<std::vector<unsigned char>> &encrypted,
                                std::vector<std::vector<unsigned char>> &decrypted) {
    auto start = std::chrono::high_resolution_clock::now();
    
    VL_VIRTUALIZATION_BEGIN;
    decrypted.resize(encrypted.size());
    for (size_t i = 0; i < encrypted.size(); ++i) {
        decrypted[i] = aes.decrypt(encrypted[i]);
    }
    VL_VIRTUALIZATION_END;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

// Generate random data of specified size
std::vector<unsigned char> generateRandomBlock(size_t size) {
    std::vector<unsigned char> block(size);
    RAND_bytes(block.data(), block.size());
    return block;
}

// Function to convert microseconds to milliseconds
double microToMilli(double microseconds) {
    return microseconds / 1000.0;
}

int main() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    try {
        // Create AES cipher object
        AESCipher aes;

        // Generate random key and IV
        if (!aes.generateKeyAndIV()) {
            std::cerr << "Failed to generate key and IV\n";
            return 1;
        }

        // Parameters for benchmark
        const size_t BLOCK_SIZE = 1024;  // 1KB blocks
        const size_t NUM_BLOCKS = 1000000;  // 1 million blocks
        const size_t BATCH_SIZE = 10000;  // Process in batches to avoid memory issues
        const size_t NUM_BATCHES = NUM_BLOCKS / BATCH_SIZE;

        std::cout << "Benchmarking AES-CBC-256 with " << NUM_BLOCKS 
                  << " blocks of " << BLOCK_SIZE << " bytes each\n";
        std::cout << "Total data size: " << (NUM_BLOCKS * BLOCK_SIZE) / (1024 * 1024) << " MB\n\n";

        // Vectors to store timing results for each batch
        std::vector<double> encryptionTimes;
        std::vector<double> decryptionTimes;

        // Keep track of total blocks processed
        size_t blocksProcessed = 0;
        
        // Process in batches to avoid excessive memory usage
        for (size_t batch = 0; batch < NUM_BATCHES; ++batch) {
            // Generate a batch of random blocks
            std::vector<std::vector<unsigned char>> blocks;

            for (size_t i = 0; i < BATCH_SIZE; ++i) {
                blocks.push_back(generateRandomBlock(BLOCK_SIZE));
            }
            
            // Vectors for encrypted and decrypted data
            std::vector<std::vector<unsigned char>> encrypted;
            std::vector<std::vector<unsigned char>> decrypted;
            
            // Measure encryption time
            double encryptTime = measureBatchEncryptionTime(aes, blocks, encrypted);
            encryptionTimes.push_back(encryptTime);
            
            // Measure decryption time
            double decryptTime = measureBatchDecryptionTime(aes, encrypted, decrypted);
            decryptionTimes.push_back(decryptTime);
            
            // Update blocks processed
            blocksProcessed += BATCH_SIZE;
            
            // Print progress
            std::cout << "Processed " << blocksProcessed << "/" << NUM_BLOCKS 
                      << " blocks (" << std::fixed << std::setprecision(1) << (blocksProcessed * 100.0) / NUM_BLOCKS << "%)\r";
            std::cout.flush();
            
            // Verify a sample (only first block in batch to save time)
            if (blocks[0] != decrypted[0]) {
                std::cerr << "\nEncryption/decryption verification failed in batch " << batch << "!\n";
                return 1;
            }
        }
        
        std::cout << "\nAll " << NUM_BLOCKS << " blocks processed successfully.\n\n";
        
        // Calculate total and average times
        double totalEncryptTime = std::accumulate(encryptionTimes.begin(), encryptionTimes.end(), 0.0);
        double totalDecryptTime = std::accumulate(decryptionTimes.begin(), decryptionTimes.end(), 0.0);
        
        double avgEncryptTimePerBlock = totalEncryptTime / NUM_BLOCKS;
        double avgDecryptTimePerBlock = totalDecryptTime / NUM_BLOCKS;
        
        // Calculate throughput
        double encryptThroughput = ((NUM_BLOCKS * BLOCK_SIZE) / totalEncryptTime) * 1000000; // Bytes per second
        double decryptThroughput = ((NUM_BLOCKS * BLOCK_SIZE) / totalDecryptTime) * 1000000; // Bytes per second
        
        // Print results
        std::cout << "--- Results ---\n";
        std::cout << "Total time:\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Encryption: " << totalEncryptTime << " us (" << microToMilli(totalEncryptTime) << " ms)\n";
        std::cout << "  Decryption: " << totalDecryptTime << " us (" << microToMilli(totalDecryptTime) << " ms)\n\n";
        
        std::cout << "Average time per block:\n";
        std::cout << "  Encryption: " << avgEncryptTimePerBlock << " us (" << microToMilli(avgEncryptTimePerBlock) << " ms)\n";
        std::cout << "  Decryption: " << avgDecryptTimePerBlock << " us (" << microToMilli(avgDecryptTimePerBlock) << " ms)\n\n";
        
        std::cout << "Total average time (encryption + decryption):\n";
        std::cout << "  Per block: " << (avgEncryptTimePerBlock + avgDecryptTimePerBlock) << " us (" 
                  << microToMilli(avgEncryptTimePerBlock + avgDecryptTimePerBlock) << " ms)\n";
        std::cout << "  Overall: " << (totalEncryptTime + totalDecryptTime) << " us (" 
                  << microToMilli(totalEncryptTime + totalDecryptTime) << " ms)\n\n";
        
        std::cout << "Throughput:\n";
        std::cout << "  Encryption: " << std::fixed << std::setprecision(2) 
                  << encryptThroughput / (1024 * 1024) << " MB/s\n";
        std::cout << "  Decryption: " << std::fixed << std::setprecision(2) 
                  << decryptThroughput / (1024 * 1024) << " MB/s\n";
        std::cout << "  Combined: " << std::fixed << std::setprecision(2)
                  << (encryptThroughput + decryptThroughput) / (2 * 1024 * 1024) << " MB/s (average)\n";
        
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // Clean up OpenSSL
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
