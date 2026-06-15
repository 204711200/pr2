#include "modul.h"
#include <iostream>
#include <string>

bool isPrime(int64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    
    std::cout << "  Проверка числа " << n << " на простоту:\n";
    for (int64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            std::cout << "    " << n << " делится на " << i << " — не простое\n";
            return false;
        }
    }
    std::cout << "    " << n << " — простое число\n";
    return true;
}

void verifyFermatTheorem(int64_t a, int64_t p) {
    std::cout << "\nПроверка теоремы Ферма\n";
    std::cout << "Теорема: если p простое, то a^(" << p-1 << ") ≡ 1 (mod " << p << ")\n";
    
    int64_t result = powerModBinary(a, p-1, p);
    std::cout << "\nРезультат: " << a << "^(" << p-1 << ") mod " << p << " = " << result << "\n";
    
    if (result == 1) {
        std::cout << "Теорема Ферма выполняется\n";
    } else {
        std::cout << "Теорема Ферма не выполняется, p не является простым\n";
    }
}

int64_t powerModFermat(int64_t a, int64_t x, int64_t p) {
    std::cout << "\nМетод 1: Через теорему Ферма\n";
    std::cout << "Вычисляем " << a << "^" << x << " mod " << p << "\n";
    
    int64_t reducedExp = x % (p - 1);
    std::cout << "Шаг 1: По теореме Ферма a^(" << p-1 << ") ≡ 1 mod " << p << "\n";
    std::cout << "Шаг 2: " << x << " = " << x/(p-1) << "·(" << p-1 << ") + " << reducedExp << "\n";
    std::cout << "Шаг 3: " << a << "^" << x << " ≡ " << a << "^" << reducedExp << " mod " << p << "\n";
    
    int64_t result = 1;
    int64_t base = a % p;
    if (base < 0) base += p;
    std::cout << "Шаг 4: Вычисляем " << base << "^" << reducedExp << " mod " << p << ":\n";
    
    for (int64_t i = 1; i <= reducedExp; i++) {
        result = (result * base) % p;
        std::cout << "    Итерация " << i << ": result = " << result << "\n";
    }
    
    std::cout << "Результат: " << result << "\n";
    return result;
}

int64_t powerModBinary(int64_t a, int64_t x, int64_t p) {
    std::cout << "\nМетод 2: Бинарное возведение в степень\n";
    std::cout << "Вычисляем " << a << "^" << x << " mod " << p << "\n";
    
    std::cout << "Шаг 1: Разложение " << x << " в двоичный вид\n";
    int64_t temp = x;
    std::string binary = "";
    while (temp > 0) {
        binary = std::to_string(temp % 2) + binary;
        temp /= 2;
    }
    if (binary.empty()) binary = "0";
    std::cout << "    " << x << " = " << binary << "_2\n";
    
    int64_t result = 1;
    int64_t base = a % p;
    if (base < 0) base += p;
    int64_t exponent = x;
    
    std::cout << "\nШаг 2: Возведение в квадрат\n";
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % p;
            std::cout << "    Бит 1: умножаем result = " << result << "\n";
        } else {
            std::cout << "    Бит 0: пропускаем умножение result = " << result << "\n";
        }
        exponent /= 2;
        if (exponent > 0) {
            base = (base * base) % p;
            std::cout << "    Возводим в квадрат: base = " << base << "\n";
        }
    }
    
    std::cout << "\nКонечный результат: " << result << "\n";
    return result;
}

void demonstratePowerMod() {
    std::cout << "\n================ ЗАДАНИЕ 1 ================\n";
    int64_t a, x, p;
    std::cout << "Основание a: "; std::cin >> a;
    std::cout << "Степень x: "; std::cin >> x;
    
    do {
        std::cout << "Модуль p (должен быть простым): ";
        std::cin >> p;
        if (!isPrime(p)) {
            std::cout << "  Ошибка: p должно быть простым числом\n";
        }
    } while (!isPrime(p));
    
    std::cout << "\nИсходные данные: a = " << a << ", x = " << x << ", p = " << p << "\n";
    verifyFermatTheorem(a, p);
    
    int64_t result1 = powerModFermat(a, x, p);
    int64_t result2 = powerModBinary(a, x, p);
    
    std::cout << "\nСравнение методов:\n";
    std::cout << "Метод Ферма:   " << a << "^" << x << " mod " << p << " = " << result1 << "\n";
    std::cout << "Бинарный метод: " << a << "^" << x << " mod " << p << " = " << result2 << "\n";
    
    if (result1 == result2) {
        std::cout << "Результаты совпадают\n";
    } else {
        std::cout << "Результаты не совпали!\n";
    }
}