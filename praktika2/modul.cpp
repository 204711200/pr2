#include "modul.h"
#include <iostream>
#include <string>

// Проверка числа на простоту (перебор делителей до корня из N)
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

// Демонстрация Малой теоремы Ферма
void verifyFermatTheorem(int64_t a, int64_t p) {
    std::cout << "\nПроверка теоремы Ферма\n";
    std::cout << "Теорема: если p простое и a не делится на p, то a^(" << p-1 << ") ≡ 1 (mod " << p << ")\n";
    
    if (a % p == 0) {
        std::cout << "Основание a = " << a << " делится на p = " << p << ". Теорема Ферма неприменима (результат всегда 0).\n";
        return;
    }
    
    int64_t result = powerModBinary(a, p-1, p);
    std::cout << "\nРезультат: " << a << "^(" << p-1 << ") mod " << p << " = " << result << "\n";
    
    if (result == 1) {
        std::cout << "Теорема Ферма выполняется\n";
    } else {
        std::cout << "Теорема Ферма не выполняется\n";
    }
}

// Метод 1: Возведение в степень с оптимизацией по теореме Ферма
int64_t powerModFermat(int64_t a, int64_t x, int64_t p) {
    std::cout << "\nМетод 1: Через теорему Ферма\n";
    std::cout << "Вычисляем " << a << "^" << x << " mod " << p << "\n";
    
    // 1. Если степень 0, результат всегда 1, независимо от основания
    if (x == 0) {
        std::cout << "Шаг 1: Степень равна 0. Любое число в нулевой степени равно 1.\n";
        std::cout << "Результат: 1\n";
        return 1;
    }
    
    // 2. Если степень > 0 и основание делится на модуль, тогда результат 0
    if (a % p == 0) {
        std::cout << "Шаг 1: Основание делится на модуль, а степень больше 0. Результат равен 0.\n";
        std::cout << "Результат: 0\n";
        return 0;
    }
    
    // Уменьшаем показатель степени по формуле x % (p - 1)
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

// Метод 2: Быстрое бинарное возведение в степень (алгоритм Square-and-Multiply)
int64_t powerModBinary(int64_t a, int64_t x, int64_t p) {
    std::cout << "\nМетод 2: Бинарное возведение в степень\n";
    std::cout << "Вычисляем " << a << "^" << x << " mod " << p << "\n";
    
    // Получение двоичного вида степени для вывода шагов
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
    // Итеративный разбор по битам степени
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % p; // Если бит равен 1 — перемножаем
            std::cout << "    Бит 1: умножаем result = " << result << "\n";
        } else {
            std::cout << "    Бит 0: пропускаем умножение result = " << result << "\n";
        }
        exponent /= 2;
        if (exponent > 0) {
            base = (base * base) % p; // Основание возводится в квадрат каждую итерацию
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