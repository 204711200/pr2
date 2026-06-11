#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <cstdint>
#include <utility>
#include <string>
#include <vector>

using namespace std;

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

    pair<int64_t, int64_t> encrypt(int64_t message, int64_t sessionKeyK);
    int64_t decrypt(int64_t a, int64_t b);

    // Работа со строками (ввод текста вручную)
    vector<pair<int64_t, int64_t>> encryptString(const string& text, int64_t sessionKeyK);
    string decryptString(const vector<pair<int64_t, int64_t>>& cipherText);

    // Работа с реальными файлами по пути на диске
    bool encryptFile(const string& inputPath, const string& outputPath, int64_t sessionKeyK);
    bool decryptFile(const string& inputPath, const string& outputPath);
};

#endif