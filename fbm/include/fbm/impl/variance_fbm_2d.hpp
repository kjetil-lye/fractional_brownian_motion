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
        // If we are on the boundary, we don't return any variance
        if (x == 0 || x == nx - 1 || y == 0 || y == nx - 1) {
            return 0;
        }

        const int local_index = y * (2 << (level - 1)) + x;

        const int index_x = (1 << (level - 1)) + x / ((nx - 1) >>
                (level - 1));
        const int index_y = (1 << (level - 1)) + y / ((nx - 1) >>
                (level - 1));



        std::cout << x << ", " << y << ": " << index_x << ", " << index_y << ": ";
        std::cout << index_x + index_y * (nx - 2) - 1 << std::endl;
        return variancefBm(level) * X[index_x + index_y * (nx - 2) - 1];
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
