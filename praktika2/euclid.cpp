#include "euclid.h"
#include <iostream>

GCDResult extendedGCD(int64_t a, int64_t b) {
    std::cout << "\nРасширенный алгоритм Евклида\n";
    std::cout << "Ищем u и v: " << a << "·u + " << b << "·v = gcd(" << a << ", " << b << ")\n\n";
    
    int64_t u1 = 1, u2 = 0, u3 = a;
    int64_t v1 = 0, v2 = 1, v3 = b;
    
    std::cout << "Начальные значения:\n";
    std::cout << "  u = (" << u1 << ", " << u2 << ", " << u3 << ")\n";
    std::cout << "  v = (" << v1 << ", " << v2 << ", " << v3 << ")\n";
    
    int step = 1;
    while (v3 != 0) {
        int64_t q = u3 / v3;
        
        std::cout << "\nШаг " << step << ":\n";
        std::cout << "  q = " << u3 << " / " << v3 << " = " << q << "\n";
        
        int64_t t1 = u1 - q * v1;
        int64_t t2 = u2 - q * v2;
        int64_t t3 = u3 - q * v3;
        
        u1 = v1; u2 = v2; u3 = v3;
        v1 = t1; v2 = t2; v3 = t3;
        
        std::cout << "  u = (" << u1 << ", " << u2 << ", " << u3 << ")\n";
        std::cout << "  v = (" << v1 << ", " << v2 << ", " << v3 << ")\n";
        
        step++;
    }
    
    std::cout << "\nРезультат:\n";
    std::cout << "gcd = " << u3 << ", u = " << u1 << ", v = " << u2 << "\n";
    std::cout << "Проверка: " << a << "·" << u1 << " + " << b << "·" << u2 << " = " << (a*u1 + b*u2) << "\n";
    
    return GCDResult{u3, u1, u2};
}

int64_t modularInverse(int64_t c, int64_t m) {
    std::cout << "\nНахождение обратного числа\n";
    std::cout << "Нужно найти d такое, что " << c << "·d = 1 (mod " << m << ")\n";
    std::cout << "Это значит: " << c << "·d + " << m << "·v = 1\n";
    
    GCDResult res = extendedGCD(c, m);
    
    if (res.gcd != 1) {
        std::cout << "\nОшибка: НОД(" << c << ", " << m << ") = " << res.gcd << " не равен 1\n";
        std::cout << "Обратного числа не существует\n";
        return -1;
    }
    
    int64_t d = res.u;
    while (d < 0) d += m;
    d = d % m;
    
    std::cout << "\nРезультат:\n";
    std::cout << c << "^(-1) mod " << m << " = " << d << "\n";
    std::cout << "Проверка: " << c << "·" << d << " mod " << m << " = " << (c * d % m) << "\n";
    
    return d;
}

void demonstrateExtendedGCD() {
    std::cout << "\n================ ЗАДАНИЕ 2 ================\n";
    int64_t a, b;
    std::cout << "Введите первое число a: "; std::cin >> a;
    std::cout << "Введите второе число b: "; std::cin >> b; 
    extendedGCD(a, b);
}

void demonstrateModularInverse() {
    std::cout << "\n================ ЗАДАНИЕ 3 ================\n";
    int64_t c, m;
    std::cout << "Введите число c: "; std::cin >> c;
    std::cout << "Введите модуль m: "; std::cin >> m;
    
    std::cout << "\nНайдём " << c << "^(-1) mod " << m << "\n";
    int64_t d = modularInverse(c, m);
    
    if (d != -1) {
        std::cout << "\nПроверка: " << c << "·" << d << " - 1 = " << (c*d - 1) 
                  << " делится на " << m << " (" << (c*d - 1)/m << "·" << m << ")\n";
    }
}