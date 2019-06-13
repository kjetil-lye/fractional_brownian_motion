#pragma once
#include <iostream>
namespace fbm {
namespace impl {

class Data1D {
public:
    Data1D(double* data, int nx) : data(data), nx(nx) {}

    double& operator()(int x) {

        return data[x];
    }

    double* data;

    int nx;
};
}}
