#pragma once
#include <cmath>
#include <vector>
#include <iostream>
namespace fbm {
namespace impl {
class VarianceFBM1D {
public:
    VarianceFBM1D(const std::vector<double>& X, int nx, double H)
        : X(X.data()), nx(nx), H(H) {}

    VarianceFBM1D(const double* X, int nx, double H)
        : X(X), nx(nx), H(H) {}

    double operator()(int x, int level) const {
        // If we are on the boundary, we don't return any variance
        if (x == 0 || x == nx - 1) {
            return 0;
        }


        // Todo: make this pure bitshift one day.
        const long long index = (1l << (level - 1)) + x / (long(nx - 1) >>
                (level - 1));

        assert(index > 0 && index < nx - 1);
        return variancefBm(level) * X[index - 1];
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
