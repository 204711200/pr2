#include "el_gamal.h"
#include "modul.h"
#include "euclid.h"
#include <iostream>
#include <fstream>

ElGamal::ElGamal(int64_t prime, int64_t generator, int64_t privateKey) {
    p = prime;
    g = generator;
    x = privateKey;
    y = 0;
}

void ElGamal::generatePublicKey() {
    y = powerModBinary(g, x, p);
    std::cout << "  [Вычисление] Открытый ключ y = g^x mod p = " << y << std::endl;
}

int64_t ElGamal::getPublicKey() const {
    return y;
}

std::pair<int64_t, int64_t> ElGamal::encrypt(int64_t message, int64_t sessionKeyK) {
    std::cout << "\n--- Процесс шифрования Эль-Гамаля ---\n";
    std::cout << "Шаг 1: Вычисляем сессионную компоненту a = g^k mod p\n";
    int64_t a = powerModBinary(g, sessionKeyK, p);
    
    std::cout << "Шаг 2: Вычисляем маскирующий множитель K = y^k mod p\n";
    int64_t y_pow_k = powerModBinary(y, sessionKeyK, p);
    
    std::cout << "Шаг 3: Маскируем сообщение b = (m * K) mod p\n";
    int64_t b = (message % p * y_pow_k) % p;
    
    std::cout << "Шифртекст сформирован: (a = " << a << ", b = " << b << ")\n";
    return {a, b};
}

int64_t ElGamal::decrypt(int64_t a, int64_t b) {
    std::cout << "\n--- Процесс дешифрования Эль-Гамаля ---\n";
    std::cout << "Шаг 1: Восстанавливаем общий секрет маски K = a^x mod p\n";
    int64_t ax = powerModBinary(a, x, p);
    
    std::cout << "Шаг 2: Находим модульное обратное к секрету K^(-1) mod p\n";
    int64_t ax_inverse = modularInverse(ax, p);
    if (ax_inverse == -1) return -1;
    
    std::cout << "Шаг 3: Снимаем маску с сообщения m = (b * K^(-1)) mod p\n";
    return (b * ax_inverse) % p;
}

std::vector<std::pair<int64_t, int64_t>> ElGamal::encryptString(const std::string& text, int64_t sessionKeyK) {
    std::vector<std::pair<int64_t, int64_t>> result;
    int64_t a = powerModBinary(g, sessionKeyK, p);
    int64_t y_pow_k = powerModBinary(y, sessionKeyK, p);

    for (char c : text) {
        int64_t message = static_cast<unsigned char>(c);
        int64_t b = (message * y_pow_k) % p;
        result.push_back({a, b});
    }
    return result;
}

std::string ElGamal::decryptString(const std::vector<std::pair<int64_t, int64_t>>& cipherText) {
    if (cipherText.empty()) return "";
    
    int64_t ax = powerModBinary(cipherText[0].first, x, p);
    int64_t ax_inverse = modularInverse(ax, p);
    if (ax_inverse == -1) return "";

    std::string result = "";
    for (const auto& pair : cipherText) {
        char c = static_cast<char>((pair.second * ax_inverse) % p);
        result += c;
    }
    return result;
}

bool ElGamal::encryptFile(const std::string& inputPath, const std::string& outputPath, int64_t sessionKeyK) {
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return false;

    char byte;
    int64_t a = powerModBinary(g, sessionKeyK, p);
    int64_t y_pow_k = powerModBinary(y, sessionKeyK, p);

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

bool ElGamal::decryptFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) return false;

    int64_t a, b;
    bool firstByte = true;
    int64_t ax_inverse = -1;

    while (inFile.read(reinterpret_cast<char*>(&a), sizeof(a)) &&
           inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (firstByte) {
            int64_t ax = powerModBinary(a, x, p);
            ax_inverse = modularInverse(ax, p);
            if (ax_inverse == -1) return false;
            firstByte = false;
        }
        char byte = static_cast<char>((b * ax_inverse) % p);
        outFile.write(&byte, 1);
    }
    inFile.close();
    outFile.close();
    return true;
}

void demonstrateElGamal() {
    std::cout << "\n================ ЗАДАНИЕ 4 ================\n";
    int64_t p, g, xA, kB;
    
    std::cout << "Введите простое число p: "; std::cin >> p;
    while (!isPrime(p)) {
        std::cout << "p должно быть простым. Введите другое число: "; std::cin >> p;
    }
    std::cout << "Введите генератор g: "; std::cin >> g;
    std::cout << "Введите секретный ключ Алисы x: "; std::cin >> xA;
    
    ElGamal alice(p, g, xA);
    alice.generatePublicKey();

    std::cout << "Введите сессионный ключ Боба k: "; std::cin >> kB;

    std::cout << "\nРежимы работы:\n1. Текст в консоли\n2. Файловый режим\nВаш выбор: ";
    int mode; std::cin >> mode;

    if (mode == 1) {
        std::string text;
        std::cout << "Введите строку текста: ";
        std::cin.ignore(); 
        std::getline(std::cin, text);

        auto cipherText = alice.encryptString(text, kB);
        std::string decryptedText = alice.decryptString(cipherText);
        std::cout << "Расшифрованная строка: \"" << decryptedText << "\"\n";
    } 
    else {
        std::string inputPath;
        std::cout << "Введите имя исходного файла: "; std::cin >> inputPath;

        std::string outputPath = inputPath + ".enc";  
        std::string decryptedPath = inputPath + ".dec"; 

        if (alice.encryptFile(inputPath, outputPath, kB)) std::cout << "Успех: файл зашифрован.\n";
        if (alice.decryptFile(outputPath, decryptedPath)) {
            std::cout << "Успех: файл расшифрован.\nСодержимое восстановленного файла: \"";
            std::ifstream resFile(decryptedPath);
            std::string content;
            while (std::getline(resFile, content)) {
                std::cout << content << (resFile.eof() ? "" : "\n");
            }
            std::cout << "\"\n";
            resFile.close();
        }
    }
}