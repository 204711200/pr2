#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>

using namespace std;

// 1. Функция вычисления НОД
int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 2. Функция вычисления суммы бесконечного ряда
bool compute_series_sum(int64_t a, int64_t b, double& sum) {
    // Если b <= 1, знаменатель ряда не растет экспоненциально, ряд расходится
    if (b <= 1) {
        return false; 
    }
    
    sum = 0.0;
    // Итерации по членам ряда n от 1 до бесконечности
    for (int64_t n = 1; n < 10000; ++n) {
        double term = pow(n, a) / pow(b, n);
        
        // Условие останова: если текущий член ряда слишком мал
        if (term < 1e-15) {
            break;
        }
        sum += term;
    }
    return true;
}

// 3. Функция вывода результата в виде несократимой дроби
void print_fraction_result(double sum) {
    int64_t precision = 1000000; // Точность перевода в дробь
    int64_t num = (int64_t)round(sum * precision); // Числитель
    int64_t den = precision;                      // Знаменатель
    
    int64_t common_divisor = gcd(num, den);
    
    // Вывод сокращенной дроби
    cout << (num / common_divisor) << "/" << (den / common_divisor) << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    int64_t a, b;
    cout << "Введите значения a и b через пробел: ";
    if (!(cin >> a >> b)) {
        cout << "Ошибка ввода параметров." << endl;
        return 0;
    }
    
    double sum = 0.0;
    
    if (!compute_series_sum(a, b, sum)) {
        cout << "infinity" << endl;
    } else {
        cout << "Результат в виде несократимой дроби: ";
        print_fraction_result(sum);
    }
    
    return 0;
}