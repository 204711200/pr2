#include <iostream>
#include <string>
#include <limits>
#include <clocale>

#include "modul.h"
#include "euclid.h"
#include "el_gamal.h"

enum class MenuOption {
    EXIT = 0,
    POWER_MOD,
    EXTENDED_EUCLID,
    MODULAR_INVERSE,
    EL_GAMAL
};

void clearInputBuffer() {
    using namespace std;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    using namespace std;
    cout << "\n--- МАТЕМАТИЧЕСКИЕ ОСНОВЫ КРИПТОГРАФИИ ---\n";
    cout << "1. Возведение в степень по модулю (Ферма / Бинарный метод)\n";
    cout << "2. Расширенный алгоритм Евклида\n";
    cout << "3. Вычисление мультипликативно обратного элемента\n";
    cout << "4. Криптосистема Эль-Гамаля (Консоль / Файлы)\n";
    cout << "0. Выход из программы\n";
    cout << "------------------------------------------\n";
    cout << "Ваш выбор: ";
}

void waitForUser() {
    using namespace std;
    cout << "\nНажмите Enter, чтобы вернуться в меню...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << string(50, '\n');
}

int main() {
    using namespace std;
    setlocale(LC_ALL, "Russian");
    
    int userChoice;
    MenuOption selectedOption = MenuOption::EXIT;
    
    do {
        printMenu();
        cin >> userChoice;
        cout << "\n";
        
        if (cin.fail() || userChoice < 0 || userChoice > 4) {
            clearInputBuffer();
            cout << "[Ошибка] Неверный ввод! Пожалуйста, введите число от 0 до 4.\n";
            continue;
        }
        
        selectedOption = static_cast<MenuOption>(userChoice);
        
        switch (selectedOption) {
            case MenuOption::POWER_MOD:
                demonstratePowerMod();
                break;
                
            case MenuOption::EXTENDED_EUCLID:
                demonstrateExtendedGCD();
                break;
                
            case MenuOption::MODULAR_INVERSE:
                demonstrateModularInverse();
                break;
                
            case MenuOption::EL_GAMAL:
                demonstrateElGamal();
                break;
                
            case MenuOption::EXIT:
                cout << "Программа успешно завершена. До свидания!\n";
                break;
        }
        
        if (selectedOption != MenuOption::EXIT) {
            waitForUser();
        }
        
    } while (selectedOption != MenuOption::EXIT);
    
    return 0;
}