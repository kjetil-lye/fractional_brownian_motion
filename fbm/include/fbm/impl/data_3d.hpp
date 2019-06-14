#pragma once
#include <iostream>
namespace fbm {
namespace impl {

struct Data3D {
    Data3D(double* data, int nx) : data(data), nx(nx), ny(nx), nz(nx) {}

    double& operator()(int x, int y, int z) {

        return data[z * nx * ny + y * nx + x];
    }

    double* data;

    int nx, ny, nz;
};
}
}
