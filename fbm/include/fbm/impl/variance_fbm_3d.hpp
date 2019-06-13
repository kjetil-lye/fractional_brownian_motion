#pragma once
#include <cmath>
namespace fbm {
namespace impl {
class VarianceFBM3D {
public:
    VarianceFBM3D(const std::vector<double>& X, int nx, double H)
        : X(X.data()), nx(nx), ny(nx), nz(nx), H(H) {}

    VarianceFBM3D(const double* X, int nx, double H)
        : X(X), nx(nx), ny(nx), nz(nx), H(H) {}

    double operator()(int x, int y, int z, int level) const {
        return variancefBm(level) * X[z * nx * ny + y * nx + x];
    }

    double variancefBm(int level) const {
        return std::sqrt(
                (1.0 - std::pow(2.0, (2 * H - 2))) / (std::pow(2, (2 * level * H))));
    }

private:
    const double* X;
    int nx, ny, nz;
    double H;
};
}
}
