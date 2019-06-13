#pragma once
#include "fbm/impl/data_3d.hpp"
#include <functional>

namespace fbm {
namespace impl {
//! Simple class that can take an qualifier for which indicies to ignore.
//!
//! Excellent for Brownian bridge where we do not want to set the boundaries
class Data3DOut {
public:
    Data3DOut(Data3D& data, std::function<bool(int, int, int)> acceptor) :
        data(data), acceptor(acceptor)
    {
        // empty
    }

    double& operator()(int x, int y, int z) {
        if (acceptor(x, y, z)) {
            return data(x, y, z);
        } else {
            return throw_away;
        }
    }
private:
    double throw_away = 42.0;
    Data3D data;
    std::function<bool(int, int, int)> acceptor;
};

}
}
