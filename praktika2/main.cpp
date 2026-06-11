#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include "crypto_math.h"
#include "el_gamal.h"

using namespace std;

enum class MenuOption {
    EXIT = 0,
    POWER_MOD = 1,
    EUCLID = 2,
    MODUL_INVERSE = 3,
    EL_GAMAL = 4,
    MITM_ATTACK = 5 // Добавлено задание 5
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showMenu() {
    cout << "\n================ МЕНЮ ================\n";
    cout << "1. Задание 1\n";
    cout << "2. Задание 2\n";
    cout << "3. Задание 3\n";
    cout << "4. Задание 4\n";
    cout << "5. Задание 5\n"; // Добавлено в вывод
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

void a_x_mod_p() {
    cout << "\n================ ЗАДАНИЕ 1 ================\n";
    int64_t a, x, p;
    cout << "Основание a: "; cin >> a;
    cout << "Степень x: "; cin >> x;
    cout << "Модуль p: "; cin >> p;

    if (isPrime(p)) {
        cout << "Число " << p << " является простым. Условия ТФ выполняются.\n";
    } else {
        cout << "Число " << p << " НЕ является простым!\n";
    }

    int64_t res = modPow(a, x, p);
    cout << "Результат: " << a << "^" << x << " mod " << p << " = " << res << "\n";
}

void algoritm_Evklida() {
    cout << "\n================ ЗАДАНИЕ 2 ================\n";
    int64_t c, m, u, v;
    cout << "Число c: "; cin >> c;
    cout << "Модуль m: "; cin >> m;

    int64_t g = extendedGcd(c, m, u, v);
    cout << "Результат:\nНОД(" << c << ", " << m << ") = " << g << "\n";
    cout << "u = " << u << "\nv = " << v << "\n";
    cout << "Проверка: " << c << " * " << u << " + " << m << " * " << v << " = " << g << "\n";
}

void obratny_element() {
    cout << "\n================ ЗАДАНИЕ 3 ================\n";
    int64_t c, m;
    cout << "Число c: "; cin >> c;
    cout << "Модуль m: "; cin >> m;

    int64_t inv = modInverse(c, m);
    if (inv == -1) {
        cout << "Обратного числа не существует, так как НОД(" << c << ", " << m << ") != 1\n";
    } else {
        cout << "Результат: " << c << "^(-1) mod " << m << " = " << inv << "\n";
        cout << "Проверка: " << c << " * " << inv << " mod " << m << " = " << (c * inv) % m << "\n";
    }
}

void El_Jamal() {
    cout << "\n================ ЗАДАНИЕ 4 ================\n";
    int64_t p, g, xA, kB;
    
    cout << "Простое число p : "; cin >> p;
    cout << "Первообразный корень g: "; cin >> g;
    
    cout << "\n[Получатель Алиса] Введите секретный ключ x: "; cin >> xA;
    ElGamal alice(p, g, xA);
    alice.generatePublicKey();

    cout << "\n[Отправитель Боб] Введите случайный сессионный ключ k: "; cin >> kB;

    cout << "\n1. Ввести текст вручную в консоли\n";
    cout << "2. Указать путь\n";
    cout << "Ваш выбор: ";
    int mode;
    cin >> mode;

    if (mode == 1) {
        string text;
        cout << "Введите строку текста для шифрования: ";
        cin.ignore(); 
        getline(cin, text);

        auto cipherText = alice.encryptString(text, kB);

        string decryptedText = alice.decryptString(cipherText);
        cout << "Расшифрованная строка: \"" << decryptedText << "\"\n";
    } 
    else if (mode == 2) {
        string inputPath;
        cout << "Введите имя/путь исходного файла: ";
        cin >> inputPath;

        string outputPath = inputPath + ".enc";  
        string decryptedPath = inputPath + ".dec"; 

        if (alice.encryptFile(inputPath, outputPath, kB)) {
            cout << "Файл зашифрован.\n";
        } else {
            cout << "Не удалось открыть исходный файл.\n";
            return;
        }

        if (alice.decryptFile(outputPath, decryptedPath)) {
            cout << "Файл расшифрован.\n";
            
            ifstream resFile(decryptedPath);
            string content;
            cout << "Содержимое восстановленного файла: \"";
            while (getline(resFile, content)) {
                cout << content << (resFile.eof() ? "" : "\n");
            }
            cout << "\"\n";
            resFile.close();
        } else {
            cout << "[Ошибка] Не удалось расшифровать файл.\n";
        }
    } 
    else {
        cout << "Неверный режим работы!\n";
    }
}

void runTask5() {
    cout << "\n================ ЗАДАНИЕ 5 ================\n";
    int64_t p, g, xA, kB, message;
    
    cout << "Простое число p: "; cin >> p;
    cout << "Первообразный корень g: "; cin >> g;
    
    cout << "\n[Алиса] Введите приватный ключ x: "; cin >> xA;
    ElGamal alice(p, g, xA);
    alice.generatePublicKey();

    cout << "\n[Боб] Введите сообщение (число m < p): "; cin >> message;
    cout << "[Боб] Введите сессионный ключ k: "; cin >> kB;

    // Генерация оригинального шифртекста
    auto cipher = alice.encrypt(message, kB);
    int64_t a = cipher.first;
    int64_t b = cipher.second;

    cout << "\n[Канал связи] Исходный шифртекст от Боба: (a = " << a << ", b = " << b << ")\n";

    // Имитация действий перехватчика
    cout << "\n[Ева] Введите множитель для изменения текста: ";
    int64_t attackFactor;
    cin >> attackFactor;

    int64_t modified_b = (b * attackFactor) % p;
    cout << "[Канал связи] Измененный Евой шифртекст: (a = " << a << ", b = " << modified_b << ")\n";

    // Алиса расшифровывает поддельный пакет
    int64_t decryptedMessage = alice.decrypt(a, modified_b);
    cout << "\n[Алиса] Результат расшифрования: " << decryptedMessage << "\n";
    cout << "  Проверка гомоморфного сдвига (m * factor mod p): " << (message * attackFactor) % p << "\n";
}

int main() {
    int choice;
    cout << "Добро пожаловать\n";

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Ошибка, введите число от 0 до 5\n";
            continue;
        }

        MenuOption option = static_cast<MenuOption>(choice);

        switch (option) {
            case MenuOption::POWER_MOD:
                a_x_mod_p();
                break;
                
            case MenuOption::EUCLID:
                algoritm_Evklida();
                break;
                
            case MenuOption::MODUL_INVERSE:
                obratny_element();
                break;
                
            case MenuOption::EL_GAMAL:
                El_Jamal();
                break;
                
            case MenuOption::MITM_ATTACK:
                runTask5();
                break;
                
            case MenuOption::EXIT:
                cout << "\nДо свидания\n";
                break;
                
            default:
                cout << "Неверный выбор\n";
                break;
        }
    } while (choice != 0);

    return 0;
}