#pragma once
#include <cmath>
#include <cassert>
#include <iostream>
namespace fbm {
namespace impl {
class VarianceFBM2D {
public:

    VarianceFBM2D(const double* X, int nx, double H, bool set_sides_to_zero = true)
        : set_sides_to_zero(set_sides_to_zero), X(X), nx(nx), ny(nx), H(H) {}

    //! @todo Figure out the global indexing here at some point
    double operator()(int x, int y, int level) const {
        if (set_sides_to_zero) {
            // If we are on the boundary, we don't return any variance
            if (x == 0 || x == nx - 1 || y == 0 || y == ny - 1) {
                return 0;
            }

            assert(counter >= 0 && counter < (nx - 2) * (nx - 2));
        } else {
            assert(counter >= 0 && counter < (nx - 1) * (nx - 1));
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
    int nx, ny;
    double H;

    mutable long long counter = 0;
};
}
}
