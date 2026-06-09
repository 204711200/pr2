#include <iostream>
#include <string>
#include <fstream>
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
    int64_t p, g, xA, kB, message;
    
    cout << "Простое число p: "; cin >> p;
    cout << "Первообразный корень g: "; cin >> g;
    
    cout << "\n[Получатель Алиса] Введите секретный ключ x: "; cin >> xA;
    ElGamal alice(p, g, xA);
    alice.generatePublicKey();

    cout << "\n[Отправитель Боб] Введите сообщение m (число): "; cin >> message;
    cout << "[Отправитель Боб] Введите сессионный ключ k: "; cin >> kB;

    auto cipher = alice.encrypt(message, kB);
    cout << "\nПереданный шифртекст: пара (a = " << cipher.first << ", b = " << cipher.second << ")\n";

    int64_t decrypted = alice.decrypt(cipher.first, cipher.second);
    cout << "\nУспешно расшифровано получателем: " << decrypted << "\n";

    // Сквозное требование №3 методички: Работа с файлами
    cout << "\n--- Интегрированное требование №3: Работа с файлами ---" << endl;
    string src = "plaintext.txt";
    string enc = "encrypted.dat";
    string dec = "decrypted.txt";

    ofstream testFile(src);
    testFile << "Novosibirsk State Technical University, NETI 2026. Binary File Protection.";
    testFile.close();

    cout << "[Файлы] Запись тестовых данных в '" << src << "'\n";
    cout << "[Файлы] Выполняется побайтовое шифрование...\n";
    alice.encryptFile(src, enc, kB);
    cout << "[Файлы] Выполняется побайтовое расшифрование...\n";
    alice.decryptFile(enc, dec);

    ifstream resFile(dec);
    string content;
    if (getline(resFile, content)) {
        cout << "[Файлы] Содержимое восстановленного файла: \"" << content << "\"\n";
    }
    resFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n--- МЕНЮ ПРАКТИЧЕСКОЙ РАБОТЫ №2 ---\n";
        cout << "1. Задание 1 (a^x mod p)\n";
        cout << "2. Задание 2 (Расширенный алгоритм Евклида)\n";
        cout << "3. Задание 3 (Обратный элемент)\n";
        cout << "4. Задание 4 (Криптосистема Эль-Гамаля + Файлы)\n";
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