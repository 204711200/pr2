#ifndef CRYPTO_MATH_H
#define CRYPTO_MATH_H

#include <cstdint>

bool isPrime(int64_t n);
int64_t modPow(int64_t base, uint64_t power, int64_t module);
int64_t extendedGcd(int64_t a, int64_t b, int64_t &u, int64_t &v);
int64_t modInverse(int64_t a, int64_t m);

#endif