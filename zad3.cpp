#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 1. Функция вычисления НОД (полностью на int)
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 2. Функция вычисления суммы ряда
bool compute_series_sum(int a, int b, double& sum) {
    if (b <= 1) return false; 
    
    sum = 0.0;
    for (int n = 1; n < 10000; ++n) {
        double term = pow(n, a) / pow(b, n);
        if (term < 1e-15) break;
        sum += term;
    }
    return true;
}

// 3. Функция вывода в виде сокращенной дроби (precision и num теперь int)
void print_fraction_result(double sum) {
    int precision = 1000000; 
    int num = (int)round(sum * precision);
    int den = precision;
    
    int common_divisor = gcd(num, den);
    cout << (num / common_divisor) << "/" << (den / common_divisor) << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int a, b;
    cout << "Введите a и b: ";
    if (!(cin >> a >> b)) return 0;
    
    double sum = 0.0;
    if (!compute_series_sum(a, b, sum)) {
        cout << "infinity" << endl;
    } else {
        cout << "Результат: ";
        print_fraction_result(sum);
    }
    return 0;
}