#include "el_gamal.h"
#include "crypto_math.h"
#include <iostream>
#include <fstream>

using namespace std;

ElGamal::ElGamal(int64_t prime, int64_t generator, int64_t privateKey) {
    p = prime;
    g = generator;
    x = privateKey;
    y = 0;
}

void ElGamal::generatePublicKey() {
    y = modPow(g, x, p);
    cout << "  [Вычисление] Открытый ключ y = g^x mod p = " << y << endl;
}

int64_t ElGamal::getPublicKey() const {
    return y;
}

std::pair<int64_t, int64_t> ElGamal::encrypt(int64_t message, int64_t sessionKeyK) {
    int64_t a = modPow(g, sessionKeyK, p);
    int64_t y_pow_k = modPow(y, sessionKeyK, p);
    int64_t b = (message % p * y_pow_k) % p;
    return {a, b};
}

int64_t ElGamal::decrypt(int64_t a, int64_t b) {
    int64_t ax = modPow(a, x, p);
    int64_t ax_inverse = modInverse(ax, p);
    if (ax_inverse == -1) return -1;
    return (b * ax_inverse) % p;
}

// Посимвольное шифрование строки (исправлено переполнение и UTF-8)
std::vector<std::pair<int64_t, int64_t>> ElGamal::encryptString(const string& text, int64_t sessionKeyK) {
    vector<pair<int64_t, int64_t>> result;
    int64_t a = modPow(g, sessionKeyK, p);
    int64_t y_pow_k = modPow(y, sessionKeyK, p);
    
    cout << "  Компонента a (общая для строки) = " << a << endl;
    cout << "  Маскирующий множитель y^k mod p = " << y_pow_k << endl;

    for (char c : text) {
        // Защита знака байта для кириллицы
        int64_t message = static_cast<unsigned char>(c);
        int64_t b = (message * y_pow_k) % p;
        result.push_back({a, b});
    }
    return result;
}

// Расшифрование строки (исправлено переполнение)
std::string ElGamal::decryptString(const vector<pair<int64_t, int64_t>>& cipherText) {
    string result = "";
    if (cipherText.empty()) return result;

    int64_t a = cipherText[0].first;
    int64_t ax = modPow(a, x, p);
    int64_t ax_inverse = modInverse(ax, p);
    if (ax_inverse == -1) return "[Ошибка дешифрования]";

    for (const auto& pair : cipherText) {
        int64_t b = pair.second;
        int64_t decryptedMessage = (b * ax_inverse) % p;
        result += static_cast<char>(decryptedMessage);
    }
    return result;
}

// Шифрование файла по пути
bool ElGamal::encryptFile(const string& inputPath, const string& outputPath, int64_t sessionKeyK) {
    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return false;

    char byte;
    int64_t a = modPow(g, sessionKeyK, p);
    int64_t y_pow_k = modPow(y, sessionKeyK, p);

    while (inFile.get(byte)) {
        int64_t message = static_cast<unsigned char>(byte);
        int64_t b = (message * y_pow_k) % p;
        outFile.write(reinterpret_cast<const char*>(&a), sizeof(a));
        outFile.write(reinterpret_cast<const char*>(&b), sizeof(b));
    }
    inFile.close();
    outFile.close();
    return true;
}

// Расшифрование файла по пути
bool ElGamal::decryptFile(const string& inputPath, const string& outputPath) {
    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return false;

    int64_t a, b;
    bool firstByte = true;
    int64_t ax_inverse = -1;

    while (inFile.read(reinterpret_cast<char*>(&a), sizeof(a)) &&
           inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (firstByte) {
            int64_t ax = modPow(a, x, p);
            ax_inverse = modInverse(ax, p);
            if (ax_inverse == -1) return false;
            firstByte = false;
        }
        int64_t decryptedMessage = (b * ax_inverse) % p;
        char byte = static_cast<char>(decryptedMessage);
        outFile.put(byte);
    }
    inFile.close();
    outFile.close();
    return true;
}