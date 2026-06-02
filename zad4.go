package main

import (
	"bufio"
	"fmt"
	"os"
)

// Функция симуляции игрового процесса по жадной стратегии
func playGame(n, m int, a []int64) int {
	scores := [2]int64{0, 0}   // scores[0] - Павел, scores[1] - Вика
	lastTake := [2]int{-1, -1} // Хранение предыдущих ходов игроков
	currentIdx := 0
	turn := 0 // 0 - Павел, 1 - Вика

	for currentIdx < n {
		var maxSum int64 = -2e18
		bestK := -1

		// Поиск лучшего хода по жадному алгоритму
		for k := 1; k <= m; k++ {
			if currentIdx+k > n {
				break
			}
			if k == lastTake[turn] {
				continue
			}

			var currentSum int64 = 0
			for i := 0; i < k; i++ {
				currentSum += a[currentIdx+i]
			}

			if currentSum > maxSum {
				maxSum = currentSum
				bestK = k
			}
		}

		// Если ходов по правилам нет, берем первое доступное количество
		if bestK == -1 {
			for k := 1; k <= m; k++ {
				if currentIdx+k <= n {
					bestK = k
					maxSum = 0
					for i := 0; i < k; i++ {
						maxSum += a[currentIdx+i]
					}
					break
				}
			}
		}

		// Фиксация хода
		scores[turn] += maxSum
		lastTake[turn] = bestK
		currentIdx += bestK

		// Смена игрока
		turn = 1 - turn
	}

	if scores[0] > scores[1] {
		return 1
	}
	return 0
}

func main() {
	// Использование буферизованного ввода для ускорения работы программы
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var n, m int
	if _, err := fmt.Fscan(reader, &n, &m); err != nil {
		return
	}

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &a[i])
	}

	// Вызов вынесенной функции
	result := playGame(n, m, a)

	fmt.Fprintln(writer, result)
}
