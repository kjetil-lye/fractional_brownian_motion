#pragma once
#include <iostream>
namespace fbm {
namespace impl {

struct Data1D {
    Data1D(double* data, int nx) : data(data), nx(nx) {}

    double& operator()(int x) {

        return data[x];
    }

    double* data;

    int nx;
};
}
}
