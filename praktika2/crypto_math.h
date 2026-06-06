#ifndef CRYPTO_MATH_H
#define CRYPTO_MATH_H

#include <cstdint>
#include <vector>

// Структуры для Эль-Гамаля
struct ElGamalPublicKey {
    int64_t p; // Простое число
    int64_t g; // Первообразный корень
    int64_t y; // Открытый ключ (y = g^x mod p)
};

struct ElGamalCiphertext {
    int64_t a; // g^k mod p
    int64_t b; // (m * y^k) mod p
};

// Базовая математика
bool is_prime(int64_t n);
int64_t power_modular_bin(int64_t a, int64_t x, int64_t p);
int64_t solve_task1_fermat(int64_t a, int64_t x, int64_t p);
int64_t extended_gcd(int64_t c, int64_t d, int64_t &u, int64_t &v);
int64_t modular_inverse(int64_t c, int64_t m);

// Задание 6*: Разложение в цепную дробь и решение Диофантова уравнения
void solve_diophantine_variant3();

#endif // CRYPTO_MATH_H