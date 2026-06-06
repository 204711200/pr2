#include "crypto_math.h"
#include <iostream>
#include <vector>

bool is_prime(int64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int64_t power_modular_bin(int64_t a, int64_t x, int64_t p) {
    int64_t result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (static_cast<__int128>(result) * a) % p;
        }
        a = (static_cast<__int128>(a) * a) % p;
        x /= 2;
    }
    return result;
}

int64_t solve_task1_fermat(int64_t a, int64_t x, int64_t p) {
    std::cout << "\n=== Задание 1: Вычисление " << a << "^" << x << " mod " << p << " ===\n";
    if (!is_prime(p)) {
        std::cout << "[Лог] Модуль не простой. Считаем бинарным возведением...\n";
        return power_modular_bin(a, x, p);
    }
    if (a % p == 0) return 0;
    
    int64_t reduced_x = x % (p - 1);
    std::cout << "[Лог] По теореме Ферма уменьшаем степень: " << x << " -> " << reduced_x << "\n";
    return power_modular_bin(a, reduced_x, p);
}

int64_t extended_gcd(int64_t c, int64_t d, int64_t &u, int64_t &v) {
    if (d == 0) {
        u = 1; v = 0;
        return c;
    }
    int64_t u1, v1;
    int64_t gcd = extended_gcd(d, c % d, u1, v1);
    u = v1;
    v = u1 - (c / d) * v1;
    return gcd;
}

int64_t modular_inverse(int64_t c, int64_t m) {
    int64_t u, v;
    int64_t gcd = extended_gcd(c, m, u, v);
    if (gcd != 1) return -1;
    return (u % m + m) % m;
}

// Задание 6*: Решение уравнения 1256a + 847b = 119
void solve_diophantine_variant3() {
    std::cout << "\n=== Задание 6*: Решение Диофантова уравнения 1256a + 847b = 119 ===\n";
    int64_t A = 1256, B = 847, C = 119;
    
    // 1. Находим НОД
    int64_t u_gcd, v_gcd;
    int64_t gcd = extended_gcd(A, B, u_gcd, v_gcd);
    std::cout << "[Шаг 1] НОД(" << A << ", " << B << ") = " << gcd << "\n";
    
    if (C % gcd != 0) {
        std::cout << "Решений нет, так как " << C << " не делится на НОД.\n";
        return;
    }
    
    // 2. Разложение A/B в цепную дробь
    std::cout << "[Шаг 2] Разложение " << A << "/" << B << " в цепную дробь:\n";
    std::vector<int64_t> q; // неполные частные
    int64_t temp_A = A, temp_B = B;
    while (temp_B != 0) {
        q.push_back(temp_A / temp_B);
        std::cout << "  " << temp_A << " = " << temp_B << " * " << q.back() << " + " << temp_A % temp_B << "\n";
        int64_t rem = temp_A % temp_B;
        temp_A = temp_B;
        temp_B = rem;
    }
    
    // 3. Вычисление подходящих дробей P_n / Q_n
    size_t n = q.size();
    std::vector<int64_t> P(n), Q(n);
    P[0] = q[0];     Q[0] = 1;
    if (n > 1) {
        P[1] = q[0] * q[1] + 1;
        Q[1] = q[1];
    }
    for (size_t i = 2; i < n; i++) {
        P[i] = q[i] * P[i-1] + P[i-2];
        Q[i] = q[i] * Q[i-1] + Q[i-2];
    }
    
    std::cout << "[Шаг 3] Предпоследняя подходящая дробь: P_" << n-2 << "/Q_" << n-2 << " = " << P[n-2] << "/" << Q[n-2] << "\n";
    
    // Частное решение исходного уравнения через свойства цепных дробей
    // P_(n-1)*Q_(n-2) - P_(n-2)*Q_(n-1) = (-1)^n
    int64_t sign = (n % 2 == 0) ? 1 : -1;
    int64_t a0 = Q[n-2] * (C / gcd) * (sign);
    int64_t b0 = -P[n-2] * (C / gcd) * (sign);
    
    std::cout << "[Результат] Частное решение уравнения:\n";
    std::cout << "  a0 = " << a0 << ", b0 = " << b0 << "\n";
    std::cout << "  Проверка: " << A << "*(" << a0 << ") + " << B << "*(" << b0 << ") = " << A*a0 + B*b0 << "\n";
    std::cout << "Общее решение: a = " << a0 << " + " << B/gcd << "*t, b = " << b0 << " - " << A/gcd << "*t (где t в Z)\n";
}