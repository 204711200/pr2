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
    cout << "\n--- Вычисления шифрования Эль-Гамаля ---" << endl;
    int64_t a = modPow(g, sessionKeyK, p);
    cout << "  Компонента a = g^k mod p = " << a << endl;

    int64_t y_pow_k = modPow(y, sessionKeyK, p);
    int64_t b = (message % p * y_pow_k) % p;
    cout << "  Компонента b = (m * y^k) mod p = " << b << endl;

    return {a, b};
}

int64_t ElGamal::decrypt(int64_t a, int64_t b) {
    cout << "\n--- Вычисления расшифрования Эль-Гамаля ---" << endl;
    int64_t ax = modPow(a, x, p);
    cout << "  Маска сессии ax = a^x mod p = " << ax << endl;

    int64_t ax_inverse = modInverse(ax, p);
    cout << "  Обратный элемент маски = " << ax_inverse << endl;

    if (ax_inverse == -1) return -1;
    return (b * ax_inverse) % p;
}

void ElGamal::encryptFile(const string& inputPath, const string& outputPath, int64_t sessionKeyK) {
    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return;

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
}

void ElGamal::decryptFile(const string& inputPath, const string& outputPath) {
    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return;

    int64_t a, b;
    bool firstByte = true;
    int64_t ax_inverse = -1;

    while (inFile.read(reinterpret_cast<char*>(&a), sizeof(a)) &&
           inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (firstByte) {
            int64_t ax = modPow(a, x, p);
            ax_inverse = modInverse(ax, p);
            if (ax_inverse == -1) return;
            firstByte = false;
        }
        int64_t decryptedMessage = (b * ax_inverse) % p;
        char byte = static_cast<char>(decryptedMessage);
        outFile.put(byte);
    }
    inFile.close();
    outFile.close();
}