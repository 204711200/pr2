#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

// Функция симуляции игрового процесса по жадной стратегии
// Принимает vector<int64_t> и возвращает 1 (Павел) или 0 (Вика / ничья)
int64_t play_game(int64_t n, int64_t m, const vector<int64_t>& a) {
    int64_t scores[2] = {0, 0};     // scores[0] - Павел, scores[1] - Вика
    int64_t last_take[2] = {-1, -1}; // Сколько карточек взял каждый на прошлом ходу
    int64_t current_idx = 0;        // Индекс текущей карточки на столе
    int64_t turn = 0;               // Чей ход: 0 - Павел, 1 - Вика
    
    while (current_idx < n) {
        // Минимальное стартовое значение для int64_t с суффиксом LL
        int64_t max_sum = -2000000000000000000LL;  
        int64_t best_k = -1;
        
        // Поиск оптимального количества карточек (от 1 до m)
        for (int64_t k = 1; k <= m; ++k) {
            if (current_idx + k > n) break;      // Выход, если карточки закончились
            if (k == last_take[turn]) continue;  // Нарушение правила: нельзя брать столько же
            
            int64_t current_sum = 0;
            for (int64_t i = 0; i < k; ++i) {
                current_sum += a[current_idx + i];
            }
            
            if (current_sum > max_sum) {
                max_sum = current_sum;
                best_k = k;
            }
        }
        
        // если из-за запрета повтора хода доступных вариантов не нашлось,
        // игрок обязан взять минимально возможное число карточек из оставшихся
        if (best_k == -1) {
            for (int64_t k = 1; k <= m; ++k) {
                if (current_idx + k <= n) {
                    best_k = k;
                    max_sum = 0;
                    for (int64_t i = 0; i < k; ++i) {
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
        
        // Передача хода следующему игроку
        turn = 1 - turn;
    }
    
    // Результат игры
    if (scores[0] > scores[1]) {
        return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int64_t n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<int64_t> a(n);
    for (int64_t i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    cout << play_game(n, m, a) << "\n";
    
    return 0;
}