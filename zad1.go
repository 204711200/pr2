package main

import (
	"fmt"
	"math"
)

// Функция для вычисления значения Y в зависимости от X (логика графика)
func calculateY(x float64) float64 {
	if x <= -1 {
		return -x - 2
	} else if x <= 0 {
		return -1 + math.Sqrt(1-x*x)
	} else if x <= 2 {
		return 2 - math.Sqrt(4-x*x)
	} else if x <= 4 {
		return -1
	} else {
		return 0.5*x - 3
	}
}

// Функция ввода-вывода: табулирование функции и построение таблицы
func printTabulatedFunction(xStart, xEnd, dx float64) {
	// Печать шапки таблицы
	fmt.Printf("%10s | %10s\n", "X", "Y")
	fmt.Println("----------------------------")

	// Цикл вычисления и вывода строк таблицы
	for x := xStart; x <= xEnd+dx/2; x += dx {
		y := calculateY(x)
		fmt.Printf("%10.2f | %10.2f\n", x, y)
	}
}

func main() {
	// Входные данные интервала и шага
	xStart := -4.0
	xEnd := 6.0
	dx := 0.5

	// В main остается только вызов управляющей функции
	printTabulatedFunction(xStart, xEnd, dx)
}
