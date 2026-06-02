#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления значения Y по графику
double calculate_y(double x) {
    if (x <= -1) {
        return -x - 2;
    } else if (x <= 0) {
        return -1 + sqrt(1 - x * x);
    } else if (x <= 2) {
        return 2 - sqrt(4 - x * x);
    } else if (x <= 4) {
        return -1;
    } else {
        return 0.5 * x - 3;
    }
}

// Функция для вывода таблицы значений
void print_tabulated_function(double x_start, double x_end, double dx) {
    cout << setw(10) << "X" << " | " << setw(10) << "Y" << endl;
    cout << "----------------------------" << endl;
    
    for (double x = x_start; x <= x_end + dx / 2; x += dx) {
        double y = calculate_y(x);
        cout << setw(10) << fixed << setprecision(2) << x 
             << " | " << setw(10) << y << endl;
    }
}

int main() {
    double x_start = -4.0;
    double x_end = 6.0;
    double dx = 0.5;

    // main теперь только запускает процесс
    print_tabulated_function(x_start, x_end, dx);

    return 0;
}