#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "crypto_math.h"
#include "el_gamal.h"

using namespace std;

void runTask1() {
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

    int64_t temp = x;
    string binary = "";
    while (temp > 0) {
        binary = to_string(temp % 2) + binary;
        temp /= 2;
    }
    cout << "Степень " << x << " в двоичной системе: " << binary << endl;

    int64_t res = modPow(a, x, p);
    cout << "Результат: " << a << "^" << x << " mod " << p << " = " << res << "\n";
}

void runTask2() {
    cout << "\n================ ЗАДАНИЕ 2 ================\n";
    int64_t c, m, u, v;
    cout << "Число c: "; cin >> c;
    cout << "Модуль m: "; cin >> m;

    int64_t g = extendedGcd(c, m, u, v);
    cout << "Результат:\nНОД(" << c << ", " << m << ") = " << g << "\n";
    cout << "u = " << u << "\nv = " << v << "\n";
    cout << "Проверка: " << c << " * " << u << " + " << m << " * " << v << " = " << g << "\n";
}

void runTask3() {
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

void runTask4() {
    cout << "\n================ ЗАДАНИЕ 4 (Шифросистема Эль-Гамаля) ================\n";
    int64_t p, g, xA, kB;
    
    cout << "Простое число p (Рекомендуется > 255 для строк): "; cin >> p;
    cout << "Первообразный корень g: "; cin >> g;
    
    cout << "\n[Получатель Алиса] Введите секретный ключ x: "; cin >> xA;
    ElGamal alice(p, g, xA);
    alice.generatePublicKey();

    cout << "\n[Отправитель Боб] Введите случайный сессионный ключ k: "; cin >> kB;

    cout << "\n--- ВЫБОР РЕЖИМА РАБОТЫ (как у Глеба) ---\n";
    cout << "1. Ввести текст вручную в консоли\n";
    cout << "2. Зашифровать реальный файл по пути на диске\n";
    cout << "Ваш выбор: ";
    int mode;
    cin >> mode;

    if (mode == 1) {
        string text;
        cout << "Введите строку текста для шифрования: ";
        cin.ignore(); 
        getline(cin, text);

        cout << "\n--- Процесс шифрования строки ---" << endl;
        auto cipherText = alice.encryptString(text, kB);
        
        cout << "\nПолученный шифртекст (пары чисел a и b для каждого символа):\n";
        for (const auto& pair : cipherText) {
            cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        cout << endl;

        cout << "\n--- Процесс расшифрования строки ---" << endl;
        string decryptedText = alice.decryptString(cipherText);
        cout << "Успешно восстановленный текст: \"" << decryptedText << "\"\n";
    } 
    else if (mode == 2) {
        string inputPath, outputPath, decryptedPath;
        cout << "Введите имя/путь исходного файла (например, plaintext.txt): ";
        cin >> inputPath;
        cout << "Введите имя для зашифрованного файла (например, encrypted.dat): ";
        cin >> outputPath;
        cout << "Введите имя для расшифрованного файла (например, decrypted.txt): ";
        cin >> decryptedPath;

        // Создаем тестовый файл, если пользователь указал стандартное имя, а файла на диске нет
        /*if (inputPath == "plaintext.txt") {
            ofstream testFile(inputPath);
            testFile << "Novosibirsk State Technical University, NETI 2026. Custom File Path Test.";
            testFile.close();
            cout << "[Инфо] Создан автоматический файл 'plaintext.txt' с тестовыми данными.\n";
        } */

        cout << "\nВыполняется побайтовое шифрование файла..." << endl;
        if (alice.encryptFile(inputPath, outputPath, kB)) {
            cout << "[Успех] Файл зашифрован и сохранен в '" << outputPath << "'\n";
        } else {
            cout << "[Ошибка] Не удалось открыть файлы для шифрования.\n";
            return;
        }

        cout << "Выполняется побайтовое расшифрование файла..." << endl;
        if (alice.decryptFile(outputPath, decryptedPath)) {
            cout << "[Успех] Файл расшифрован и сохранен в '" << decryptedPath << "'\n";
            
            ifstream resFile(decryptedPath);
            string content;
            if (getline(resFile, content)) {
                cout << "[Результат] Содержимое восстановленного файла: \"" << content << "\"\n";
            }
            resFile.close();
        } else {
            cout << "[Ошибка] Не удалось расшифровать файл.\n";
        }
    } 
    else {
        cout << "Неверный режим работы!\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- МЕНЮ ПРАКТИЧЕСКОЙ РАБОТЫ №2 ---\n";
        cout << "1. Задание 1 (a^x mod p)\n";
        cout << "2. Задание 2 (Расширенный алгоритм Евклида)\n";
        cout << "3. Задание 3 (Обратный элемент)\n";
        cout << "4. Задание 4 (Криптосистема Эль-Гамаля: Текст / Путь к файлу)\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: runTask1(); break;
            case 2: runTask2(); break;
            case 3: runTask3(); break;
            case 4: runTask4(); break;
            case 0: cout << "Выход из программы.\n"; break;
            default: cout << "Неверный пункт меню!\n";
        }
    } while (choice != 0);
    return 0;
}