#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <string>
#include "crypto_math.h"

// Задание 4: Реализация криптосистемы Эль-Гамаля для файлов
void run_elgamal_file_protocol();

// Функции побайтового шифрования/расшифрования Эль-Гамаля
bool elgamal_encrypt_file(const std::string& input_path, const std::string& output_path, ElGamalPublicKey pub_key, int64_t secret_k);
bool elgamal_decrypt_file(const std::string& input_path, const std::string& output_path, ElGamalPublicKey pub_key, int64_t private_x);

#endif // FILE_CIPHER_H