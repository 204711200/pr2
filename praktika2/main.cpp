#include <iostream>
#include <string>
#include <limits>
#include "modul.h"
#include "euclid.h"
#include "el_gamal.h"

enum class MenuOption {
    EXIT = 0,
    POWER_MOD = 1,
    EUCLID = 2,
    MODUL_INVERSE = 3,
    EL_GAMAL = 4
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu() {
    std::cout << "\n================ МЕНЮ ================\n";
    std::cout << "1. Задание 1\n";
    std::cout << "2. Задание 2\n";
    std::cout << "3. Задание 3\n";
    std::cout << "4. Задание 4\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    int choice; 
    std::cout << "Добро пожаловать\n";
    
    do {
        showMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "Ошибка, введите число от 0 до 4\n";
            continue;
        }
        
        MenuOption option = static_cast<MenuOption>(choice);
        
        switch (option) {
            case MenuOption::POWER_MOD:
                demonstratePowerMod();
                break;
            case MenuOption::EUCLID:
                demonstrateExtendedGCD();
                break;
            case MenuOption::MODUL_INVERSE:
                demonstrateModularInverse();
                break;
            case MenuOption::EL_GAMAL:
                demonstrateElGamal();
                break;
            case MenuOption::EXIT:
                std::cout << "\nДо свидания\n";
                break;
            default:
                std::cout << "Неверный выбор\n";
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}