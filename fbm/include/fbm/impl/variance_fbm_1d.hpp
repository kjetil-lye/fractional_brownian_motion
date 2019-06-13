#pragma once
#include <cmath>
#include <vector>
namespace fbm {
namespace impl {
class VarianceFBM1D {
public:
    VarianceFBM1D(const std::vector<double>& X, int nx, double H)
        : X(X.data()), nx(nx), H(H) {}

    VarianceFBM1D(const double* X, int nx, double H)
        : X(X), nx(nx), H(H) {}

    double operator()(int x, int level) const {
        return variancefBm(level) * X[x];
    }

    double variancefBm(int level) const {
        return std::sqrt(
                (1.0 - std::pow(2.0, (2 * H - 2))) / (std::pow(2, (2 * level * H))));
    }

private:
    const double* X;
    int nx;
    double H;
};
}
}
