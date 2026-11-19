#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "CorrAnalysis.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 1] Перевірка СТАТИЧНОЇ бібліотеки CorrAnalysis (Варіант 7 - Студент Б) ===\n\n";

    double x[] = { 10.0, 20.0, 30.0, 40.0, 50.0, 60.0 };
    double y[] = { 12.0, 25.0, 28.0, 45.0, 48.0, 65.0 };
    int n = 6;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Коваріація (covariance):          " << covariance(x, y, n) << "\n";
    std::cout << "Кореляція Пірсона (pearson):      " << pearson(x, y, n) << "\n";
    std::cout << "Кореляція Спірмена (spearman):    " << spearman(x, y, n) << "\n";

    double data[3 * 6] = {
        10.0, 20.0, 30.0, 40.0, 50.0, 60.0,
        12.0, 25.0, 28.0, 45.0, 48.0, 65.0,
        60.0, 52.0, 41.0, 29.0, 18.0, 10.0
    };
    double mat[9]{};
    if (correlationMatrix(data, 3, 6, mat) == 0) {
        std::cout << "\nКореляційна матриця (3x3):\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << std::setw(9) << mat[i * 3 + j] << " ";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n[Перевірка граничних випадків (Edge Cases)]:\n";
    double constArr[] = { 7.0, 7.0, 7.0, 7.0, 7.0, 7.0 };
    std::cout << "1) nullptr масив -> pearson = " << pearson(nullptr, y, n) << " (очікується nan)\n";
    std::cout << "2) n = 1 (< 2) -> covariance = " << covariance(x, y, 1) << " (очікується nan)\n";
    std::cout << "3) Нульова дисперсія -> pearson = " << pearson(constArr, y, n) << " (очікується nan)\n";
    std::cout << "4) nullptr для матриці -> код = " << correlationMatrix(data, 3, 6, nullptr) << " (очікується -1)\n";

    return 0;
}
