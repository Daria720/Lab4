#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "StatAnalysis.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 3.1] НЕЯВНЕ зв'язування (Implicit Linking) StatAnalysis.dll ===\n";
    std::cout << "Виконавець: Студент Б | Бібліотека партнера: StatAnalysis\n\n";

    double values[] = { 42.0, 48.5, 53.0, 59.5, 64.0, 71.0, 88.0 };
    int n = 7;

    std::cout << "Вхідна вибірка (n = " << n << "): ";
    for (int i = 0; i < n; ++i) std::cout << values[i] << (i + 1 < n ? ", " : "\n");

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Середнє арифметичне (mean):      " << mean(values, n) << "\n";
    std::cout << "Вибіркова дисперсія (variance):  " << variance(values, n, 1) << "\n";
    std::cout << "Стандартне відхилення (stdDev):  " << stdDev(values, n, 1) << "\n";
    std::cout << "Медіана (median):                " << median(values, n) << "\n";

    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    int status = quartiles(values, n, &q1, &q2, &q3);
    std::cout << "Квартилі (status = " << status << "):           Q1=" << q1 << ", Q2=" << q2 << ", Q3=" << q3 << "\n";

    std::cout << "\n--- Тестування граничних випадків (Edge Cases) контракту партнера ---\n";
    std::cout << "1) Передача nullptr: mean(nullptr, 5) = " << mean(nullptr, 5) << "\n";
    std::cout << "2) Розмір n = 1 для вибіркової дисперсії: variance(values, 1, 1) = " << variance(values, 1, 1) << "\n";
    std::cout << "3) Нульовий розмір вибірки: median(values, 0) = " << median(values, 0) << "\n";
    std::cout << "4) Некоректний вихідний вказівник (nullptr): quartiles code = " << quartiles(values, n, nullptr, &q2, &q3) << "\n";

    return 0;
}
