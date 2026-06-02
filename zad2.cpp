#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef unsigned long long uint64;

// Модульное возведение в степень (a^b mod n)
uint64 power(uint64 a, uint64 b, uint64 n) {
    uint64 res = 1;
    a %= n;
    while (b > 0) {
        if (b % 2 == 1) res = (__uint128_t)res * a % n;
        a = (__uint128_t)a * a % n;
        b /= 2;
    }
    return res;
}

uint64 generate_gost_p(uint64 q, int t, double xi) {
    // Предварительный расчет границ
    uint64 pow_2_t_minus_1 = (uint64)1 << (t - 1);
    uint64 pow_2_t = (uint64)1 << t;

    // Вычисляем N
    // Формула: N = ceil(2^(t-1) / q) + ceil(2^(t-1) * xi / q)
    uint64 N = (uint64)ceil((double)pow_2_t_minus_1 / q) + 
               (uint64)ceil((double)pow_2_t_minus_1 * xi / q);

    // Если N нечетное, то N = N + 1
    if (N % 2 != 0) N++;

    // Задаем u = 0
    uint64 u = 0;

    while (true) {
        // Вычисляем p = (N + u) * q + 1
        uint64 p = (N + u) * q + 1;

        // Если p > 2^t, вернуться на шаг 1 (в нашем случае - к новому xi)
        if (p > pow_2_t) return 0; 

        // Проверка условий теоремы Диемитко
        // 1) 2^(p-1) == 1 (mod p)
        // 2) 2^(N+u) != 1 (mod p)
        if (power(2, p - 1, p) == 1 && power(2, N + u, p) != 1) {
            return p; // Выход: p - простое число
        }

        // u = u + 2
        u += 2;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    uint64 q;
    int t;
    double xi = 0; // Для совпадения с таблицей используем xi = 0

    cout << "--- Проверка по таблице Приложения Г (xi = 0) ---" << endl;
    cout << "Введите q (базовое простое): ";
    cin >> q;
    cout << "Введите t (разрядность p): ";
    cin >> t;

    uint64 p = generate_gost_p(q, t, xi);

    if (p != 0) {
        cout << "\nРезультат:" << endl;
        cout << "------------------------------------" << endl;
        cout << "q = " << q << ", t = " << t << " => p = " << p << endl;
        cout << "------------------------------------" << endl;
        cout << "Проверка по теореме Диемитко: Пройдена" << endl;
    } else {
        cout << "Число не найдено в заданном диапазоне." << endl;
    }

    return 0;
}