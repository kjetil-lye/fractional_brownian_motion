#pragma once
#include "fbm/impl/data_2d.hpp"
#include <functional>

namespace fbm {
namespace impl {
//! Simple class that can take an qualifier for which indicies to ignore.
//!
//! Excellent for Brownian bridge where we do not want to set the boundaries
class Data2DOut {
public:
    Data2DOut(Data2D& data, std::function<bool(int, int)> acceptor) :
        data(data), acceptor(acceptor)
    {
        // empty
    }

    double& operator()(int x, int y) {
        if (acceptor(x, y)) {
            return data(x, y);
        } else {
            return throw_away;
        }
    }
private:
    double throw_away = 42.0;
    Data2D data;
    std::function<bool(int, int)> acceptor;
};

}
}
