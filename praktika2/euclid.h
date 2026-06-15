#ifndef EUCLID_H
#define EUCLID_H

#include <cstdint>

struct GCDResult {
    int64_t gcd;
    int64_t u;
    int64_t v;
};

GCDResult extendedGCD(int64_t a, int64_t b);
int64_t modularInverse(int64_t c, int64_t m);

void demonstrateExtendedGCD();
void demonstrateModularInverse();

#endif