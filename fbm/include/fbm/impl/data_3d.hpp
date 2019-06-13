#pragma once
#include <iostream>
namespace fbm {
namespace impl {

class Data3D {
public:
    Data3D(double* data, int nx) : data(data), nx(nx), ny(nx), nz(nx) {}

    double& operator()(int x, int y, int z) {

        return data[z * nx * ny + y * nx + x];
    }

    double* data;

    int nx, ny, nz;
};
}}
