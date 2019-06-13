#pragma once
#include <iostream>
namespace fbm {
namespace impl {

class Data2D {
public:
    Data2D(double* data, int nx) : data(data), nx(nx), ny(nx) {}

    double& operator()(int x, int y) {

        return data[y * nx + x];
    }

    double* data;

    int nx, ny;
};
}}
