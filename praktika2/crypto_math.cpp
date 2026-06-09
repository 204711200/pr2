#include "crypto_math.h"
#include <iostream>
#include <string>

using namespace std;

// Проверка числа на простоту
bool isPrime(int64_t n) {
    if (n < 2) return false;
    for (int64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Задание 1: Бинарное возведение в степень по модулю (с защитой от зависаний)
int64_t modPow(int64_t base, uint64_t power, int64_t module) {
    if (module <= 1) return 0;
    int64_t result = 1;
    base = base % module;
    if (base < 0) base += module; 

    while (power > 0) {
        if (power & 1) {
            result = (result * base) % module;
        }
        base = (base * base) % module;
        power >>= 1; 
    }
    return result;
}

// Задание 2: Расширенный алгоритм Евклида
int64_t extendedGcd(int64_t a, int64_t b, int64_t &u, int64_t &v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int64_t u1, v1;
    int64_t g = extendedGcd(b, a % b, u1, v1);
    u = v1;
    v = u1 - (a / b) * v1;
    return g;
}

// Задание 3: Нахождение обратного элемента по модулю
int64_t modInverse(int64_t a, int64_t m) {
    int64_t u, v;
    int64_t g = extendedGcd(a, m, u, v);
    if (g != 1) return -1; 
    return (u % m + m) % m;
}