#include "el_gamal.h"
#include "crypto_math.h"
#include <iostream>
#include <fstream>

bool elgamal_encrypt_file(const std::string& input_path, const std::string& output_path, ElGamalPublicKey pub_key, int64_t secret_k) {
    std::ifstream in(input_path, std::ios::binary);
    std::ofstream out(output_path, std::ios::binary);
    if (!in || !out) return false;

    std::cout << "\n[Эль-Гамаль Шифрование] Обработка файла...\n";
    char byte;
    while (in.get(byte)) {
        int64_t m = static_cast<uint8_t>(byte);
        
        // а = g^k mod p
        int64_t a = power_modular_bin(pub_key.g, secret_k, pub_key.p);
        // b = (m * y^k) mod p
        int64_t y_k = power_modular_bin(pub_key.y, secret_k, pub_key.p);
        int64_t b = (static_cast<__int128>(m) * y_k) % pub_key.p;

        // Записываем пару (a, b) в файл. Каждый элемент сохраняем как int64_t (8 байт)
        out.write(reinterpret_cast<const char*>(&a), sizeof(a));
        out.write(reinterpret_cast<const char*>(&b), sizeof(b));
    }
    return true;
}

bool elgamal_decrypt_file(const std::string& input_path, const std::string& output_path, ElGamalPublicKey pub_key, int64_t private_x) {
    std::ifstream in(input_path, std::ios::binary);
    std::ofstream out(output_path, std::ios::binary);
    if (!in || !out) return false;

    std::cout << "[Эль-Гамаль Расшифрование] Обработка зашифрованного файла...\n";
    int64_t a, b;
    while (in.read(reinterpret_cast<char*>(&a), sizeof(a)) && in.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        // m = b * (a^x)^-1 mod p
        int64_t ax = power_modular_bin(a, private_x, pub_key.p);
        int64_t ax_inv = modular_inverse(ax, pub_key.p);
        
        if (ax_inv == -1) {
            std::cerr << "[Ошибка] Не удалось найти обратный элемент при дешифровании!\n";
            return false;
        }
        
        int64_t m = (static_cast<__int128>(b) * ax_inv) % pub_key.p;
        char decrypted_byte = static_cast<char>(m);
        out.put(decrypted_byte);
    }
    return true;
}

void run_elgamal_file_protocol() {
    std::cout << "\n=== Задание 4: Криптосистема Эль-Гамаля (Вариант 3) ===\n";
    
    // Параметры системы (выбираются безопасные p > 256)
    int64_t p = 683; // Простое число
    int64_t g = 5;   // Первообразный корень
    int64_t x = 123; // Секретный ключ получателя (x < p)
    
    // Открытый ключ y = g^x mod p
    int64_t y = power_modular_bin(g, x, p);
    ElGamalPublicKey pub_key = {p, g, y};

    std::cout << "[Ключи] Сгенерированы:\n";
    std::cout << "  Открытый ключ (p=" << p << ", g=" << g << ", y=" << y << ")\n";
    std::cout << "  Закрытый ключ (x=" << x << ")\n";

    // Создаем тестовый файл
    std::string src = "input_v3.txt";
    std::string enc = "encrypted_v3.bin";
    std::string dec = "decrypted_v3.txt";

    std::ofstream out(src);
    out << "Secret Text for Variant 3 (El-Gamal)";
    out.close();

    // Случайная сессионная переменная отправителя k (должна быть взаимно проста с p-1)
    int64_t k = 17; 

    // Шифруем и расшифровываем
    if (elgamal_encrypt_file(src, enc, pub_key, k)) {
        std::cout << "[Успех] Файл зашифрован в '" << enc << "'\n";
    }
    if (elgamal_decrypt_file(enc, dec, pub_key, x)) {
        std::cout << "[Успех] Файл расшифрован в '" << dec << "'\n";
    }
}