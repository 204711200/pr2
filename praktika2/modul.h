#ifndef MODUL_H
#define MODUL_H

#include <cstdint>

bool isPrime(int64_t n);
void verifyFermatTheorem(int64_t a, int64_t p);
int64_t powerModFermat(int64_t a, int64_t x, int64_t p);
int64_t powerModBinary(int64_t a, int64_t x, int64_t p);

int64_t readPrimeModule();

void demonstratePowerMod();

#endif