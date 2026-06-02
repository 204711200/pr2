package main

import (
	"fmt"
	"math"
)

// 1. Функция вычисления НОД (используем int вместо int64)
func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

// 2. Функция вычисления суммы бесконечного ряда
func computeSeriesSum(a, b int) (float64, bool) {
	if b <= 1 {
		return 0, false // Ряд расходится
	}

	var sum float64 = 0.0
	for n := 1; n < 10000; n++ {
		term := math.Pow(float64(n), float64(a)) / math.Pow(float64(b), float64(n))

		if term < 1e-15 {
			break
		}
		sum += term
	}
	return sum, true
}

// 3. Функция форматированного вывода результата в виде несократимой дроби
func printFractionResult(sum float64) {
	precision := 1000000
	num := int(math.Round(sum * float64(precision)))
	den := precision

	commonDivisor := gcd(num, den)

	// Вывод сокращенной дроби
	fmt.Printf("%d/%d\n", num/commonDivisor, den/commonDivisor)
}

func main() {
	var a, b int
	fmt.Print("Введите значения a и b через пробел: ")
	if _, err := fmt.Scan(&a, &b); err != nil {
		fmt.Println("Ошибка ввода параметров.")
		return
	}

	sum, converges := computeSeriesSum(a, b)

	if !converges {
		fmt.Println("infinity")
	} else {
		fmt.Print("Результат: ")
		printFractionResult(sum)
	}
}
