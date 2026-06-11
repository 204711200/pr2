#include "crypto_math.h"
#include <iostream>
#include <string>

using namespace std;

bool isPrime(int64_t n) {
    if (n < 2) return false;
    for (int64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int64_t modPow(int64_t base, uint64_t power, int64_t module) {
    if (module <= 1) return 0;
    int64_t result = 1;
    base = base % module;
    if (base < 0) base += module; 

    // Вывод начальных данных для протоколирования шагов
    cout << "  [Шаг] Инициализация: base = " << base << ", power = " << power << "\n";

    int step = 1;
    while (power > 0) {
        if (power & 1) {
            result = (result * base) % module;
            cout << "    Итерация " << step << ": бит степени = 1, текущий result = " << result << "\n";
        } else {
            cout << "    Итерация " << step << ": бит степени = 0, result без изменений\n";
        }
        base = (base * base) % module;
        power >>= 1; 
        step++;
    }
    return result;
}

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
    
    // Показываем промежуточные коэффициенты Безу на обратном ходу рекурсии
    cout << "  [Рекурсия] НОД(" << a << ", " << b << "): u = " << u << ", v = " << v << "\n";
    return g;
}

int64_t modInverse(int64_t a, int64_t m) {
    int64_t u, v;
    int64_t g = extendedGcd(a, m, u, v);
    if (g != 1) return -1; 
    return (u % m + m) % m;
}