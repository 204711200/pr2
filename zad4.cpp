#include <iostream>
#include <vector>

using namespace std;

// Функция симуляции игрового процесса по жадной стратегии
// Возвращает 1, если побеждает Павел, и 0, если побеждает Вика (или ничья)
int play_game(int n, int m, const vector<long long>& a) {
    long long scores[2] = {0, 0};   // scores[0] - Павел, scores[1] - Вика
    int last_take[2] = {-1, -1};    // Сколько карточек взял каждый на прошлом ходу
    int current_idx = 0;            // Индекс текущей карточки на столе
    int turn = 0;                   // Чей ход: 0 - Павел, 1 - Вика
    
    while (current_idx < n) {
        long long max_sum = -2e18;  // Минимальное стартовое значение для поиска максимума
        int best_k = -1;
        
        // Поиск оптимального количества карточек (от 1 до m)
        for (int k = 1; k <= m; ++k) {
            if (current_idx + k > n) break;      // Выход, если карточки закончились
            if (k == last_take[turn]) continue;  // Нарушение правила: нельзя брать столько же
            
            long long current_sum = 0;
            for (int i = 0; i < k; ++i) {
                current_sum += a[current_idx + i];
            }
            
            if (current_sum > max_sum) {
                max_sum = current_sum;
                best_k = k;
            }
        }
        
        // Форс-мажор: если из-за запрета повтора хода доступных вариантов не нашлось,
        // игрок обязан взять минимально возможное число карточек из оставшихся
        if (best_k == -1) {
            for (int k = 1; k <= m; ++k) {
                if (current_idx + k <= n) {
                    best_k = k;
                    max_sum = 0;
                    for (int i = 0; i < k; ++i) {
                        max_sum += a[current_idx + i];
                    }
                    break;
                }
            }
        }
        
        // Обновление состояния игры после сделанного хода
        scores[turn] += max_sum;
        last_take[turn] = best_k;
        current_idx += best_k;
        
        // Передача хода следующему игроку (0 превращается в 1, 1 в 0)
        turn = 1 - turn;
    }
    
    // Результат игры
    if (scores[0] > scores[1]) {
        return 1;
    }
    return 0;
}

int main() {
    // Настройка быстрой работы ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // В функции main остался только вызов изолированной логики и вывод
    cout << play_game(n, m, a) << "\n";
    
    return 0;
}