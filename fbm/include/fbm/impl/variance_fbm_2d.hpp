#pragma once
#include <cmath>
namespace fbm {
namespace impl {
class VarianceFBM2D {
public:
    VarianceFBM2D(const std::vector<double>& X, int nx, double H)
        : X(X.data()), nx(nx), ny(nx), H(H) {}

    VarianceFBM2D(const double* X, int nx, double H)
        : X(X), nx(nx), ny(nx), H(H) {}

    double operator()(int x, int y, int level) const {
        return variancefBm(level) * X[y * nx + x];
    }

    double variancefBm(int level) const {
        return std::sqrt(
                (1.0 - std::pow(2.0, (2 * H - 2))) / (std::pow(2, (2 * level * H))));
    }

private:
    const double* X;
    int nx, ny;
    double H;
};
}
}
