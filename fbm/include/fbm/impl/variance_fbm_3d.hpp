#pragma once
#include <cmath>
#include <cassert>

namespace fbm {
namespace impl {
class VarianceFBM3D {
public:
    VarianceFBM3D(const double* X, int nx, double H, bool set_sides_to_zero = false)
        : set_sides_to_zero(set_sides_to_zero), X(X), nx(nx), ny(nx), nz(nx), H(H) {}

    double operator()(int x, int y, int z, int level) const {
        if (set_sides_to_zero) {
            // If we are on the boundary, we don't return any variance
            if (x == 0 || x == nx - 1 || y == 0 || y == ny - 1 || z == 0 || z == nz - 1) {
                return 0;
            }

            assert(counter >= 0 && counter < (nx - 2) * (nx - 2) * (nx - 2));
        } else {
            assert(counter >= 0 && counter < (nx) * (nx) * (nx));
        }


        return variancefBm(level) * X[counter++];
    }

    double variancefBm(int level) const {
        return std::sqrt(
                (1.0 - std::pow(2.0, (2 * H - 2))) / (std::pow(2, (2 * level * H))));
    }

private:
    bool set_sides_to_zero;
    const double* X;
    int nx, ny, nz;
    double H;

    mutable long long counter = 0;
};
}
}
