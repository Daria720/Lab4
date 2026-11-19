#include "CorrAnalysis.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

static bool isValidArray(const double* arr, int n) {
    if (arr == nullptr || n < 2) return false;
    for (int i = 0; i < n; ++i) {
        if (std::isnan(arr[i]) || std::isinf(arr[i])) return false;
    }
    return true;
}

static std::vector<double> computeRanks(const double* arr, int n) {
    std::vector<std::pair<double, int>> indexed(n);
    for (int i = 0; i < n; ++i) {
        indexed[i] = { arr[i], i };
    }
    std::sort(indexed.begin(), indexed.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    std::vector<double> ranks(n, 0.0);
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && indexed[j + 1].first == indexed[i].first) {
            ++j;
        }
        // Середній ранг для зв'язаних рангів (ties), нумерація з 1
        double avgRank = 0.5 * (i + j) + 1.0;
        for (int k = i; k <= j; ++k) {
            ranks[indexed[k].second] = avgRank;
        }
        i = j + 1;
    }
    return ranks;
}

extern "C" {

double covariance(const double* x, const double* y, int n) {
    if (!isValidArray(x, n) || !isValidArray(y, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double meanX = 0.0, meanY = 0.0;
    for (int i = 0; i < n; ++i) {
        meanX += x[i];
        meanY += y[i];
    }
    meanX /= n;
    meanY /= n;

    double cov = 0.0;
    for (int i = 0; i < n; ++i) {
        cov += (x[i] - meanX) * (y[i] - meanY);
    }
    return cov / static_cast<double>(n - 1);
}

double pearson(const double* x, const double* y, int n) {
    if (!isValidArray(x, n) || !isValidArray(y, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double meanX = 0.0, meanY = 0.0;
    for (int i = 0; i < n; ++i) {
        meanX += x[i];
        meanY += y[i];
    }
    meanX /= n;
    meanY /= n;

    double num = 0.0, denX = 0.0, denY = 0.0;
    for (int i = 0; i < n; ++i) {
        double dx = x[i] - meanX;
        double dy = y[i] - meanY;
        num += dx * dy;
        denX += dx * dx;
        denY += dy * dy;
    }
    if (denX <= 1e-15 || denY <= 1e-15) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double r = num / std::sqrt(denX * denY);
    if (r > 1.0) r = 1.0;
    if (r < -1.0) r = -1.0;
    return r;
}

double spearman(const double* x, const double* y, int n) {
    if (!isValidArray(x, n) || !isValidArray(y, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    std::vector<double> rx = computeRanks(x, n);
    std::vector<double> ry = computeRanks(y, n);
    return pearson(rx.data(), ry.data(), n);
}

int correlationMatrix(const double* data, int vars, int n, double* outMatrix) {
    if (data == nullptr || outMatrix == nullptr || vars <= 0 || n < 2) {
        return -1;
    }
    for (int v = 0; v < vars; ++v) {
        if (!isValidArray(data + v * n, n)) return -1;
    }
    for (int i = 0; i < vars; ++i) {
        outMatrix[i * vars + i] = 1.0;
        for (int j = i + 1; j < vars; ++j) {
            double r = pearson(data + i * n, data + j * n, n);
            outMatrix[i * vars + j] = r;
            outMatrix[j * vars + i] = r;
        }
    }
    return 0;
}

} // extern "C"
