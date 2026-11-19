#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

// Оголошення типів покажчиків на функції згідно з Контрактом (без #include "StatAnalysis.h")
typedef double (*MeanFunc)(const double*, int);
typedef double (*VarianceFunc)(const double*, int, int);
typedef double (*StdDevFunc)(const double*, int, int);
typedef double (*MedianFunc)(const double*, int);
typedef int    (*QuartilesFunc)(const double*, int, double*, double*, double*);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 3.2] ЯВНЕ зв'язування (Explicit Linking) StatAnalysis.dll ===\n";
    std::cout << "Виконавець: Студент Б | Завантаження через LoadLibrary/GetProcAddress\n\n";

    HMODULE hDll = LoadLibraryA("StatAnalysis.dll");
    if (!hDll) {
        std::cerr << "[ПОМИЛКА] Не вдалося завантажити StatAnalysis.dll! Код WinAPI: " << GetLastError() << "\n";
        return 1;
    }
    std::cout << "[OK] Бібліотеку StatAnalysis.dll успішно завантажено в адресний простір процесу.\n";

    auto fnMean   = reinterpret_cast<MeanFunc>(GetProcAddress(hDll, "mean"));
    auto fnVar    = reinterpret_cast<VarianceFunc>(GetProcAddress(hDll, "variance"));
    auto fnStd    = reinterpret_cast<StdDevFunc>(GetProcAddress(hDll, "stdDev"));
    auto fnMedian = reinterpret_cast<MedianFunc>(GetProcAddress(hDll, "median"));
    auto fnQuart  = reinterpret_cast<QuartilesFunc>(GetProcAddress(hDll, "quartiles"));

    if (!fnMean || !fnVar || !fnStd || !fnMedian || !fnQuart) {
        std::cerr << "[ПОМИЛКА] Не знайдено одну або декілька експортованих функцій у DLL!\n";
        FreeLibrary(hDll);
        return 1;
    }
    std::cout << "[OK] Усі 5 адрес функцій успішно отримано через GetProcAddress().\n\n";

    double values[] = { 10.0, 20.0, 30.0, 40.0, 50.0 };
    int n = 5;
    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    fnQuart(values, n, &q1, &q2, &q3);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Виклик fnMean(values, 5)     = " << fnMean(values, n) << "\n";
    std::cout << "Виклик fnVar(values, 5, 1)   = " << fnVar(values, n, 1) << "\n";
    std::cout << "Виклик fnStd(values, 5, 1)   = " << fnStd(values, n, 1) << "\n";
    std::cout << "Виклик fnMedian(values, 5)   = " << fnMedian(values, n) << "\n";
    std::cout << "Виклик fnQuart(values, 5)    = Q1=" << q1 << ", Q2=" << q2 << ", Q3=" << q3 << "\n";

    // Перевірка граничного випадку при явному виклику
    double nanCheck = fnMean(nullptr, n);
    std::cout << "\nПеревірка Edge Case (nullptr): fnMean(nullptr, 5) = " << nanCheck << "\n";

    FreeLibrary(hDll);
    std::cout << "\n[OK] Бібліотеку StatAnalysis.dll коректно вивантажено через FreeLibrary().\n";
    return 0;
}
