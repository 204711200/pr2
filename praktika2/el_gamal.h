#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <cstdint>
#include <utility>
#include <string>
#include <vector>

class ElGamal {
private:
    int64_t p; 
    int64_t g; 
    int64_t x; 
    int64_t y; 

public:
    ElGamal(int64_t prime, int64_t generator, int64_t privateKey);
    
    void generatePublicKey();
    int64_t getPublicKey() const;

    std::pair<int64_t, int64_t> encrypt(int64_t message, int64_t sessionKeyK);
    int64_t decrypt(int64_t a, int64_t b);

    std::vector<std::pair<int64_t, int64_t>> encryptString(const std::string& text, int64_t sessionKeyK);
    std::string decryptString(const std::vector<std::pair<int64_t, int64_t>>& cipherText);

    bool encryptFile(const std::string& inputPath, const std::string& outputPath, int64_t sessionKeyK);
    bool decryptFile(const std::string& inputPath, const std::string& outputPath);
};

void processConsoleMode(ElGamal& cipher, int64_t sessionKey);
void processFileMode(ElGamal& cipher, int64_t sessionKey);

void demonstrateElGamal();

#endif