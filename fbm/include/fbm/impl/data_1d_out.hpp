#pragma once
#include "fbm/impl/data_1d.hpp"
#include <functional>

namespace fbm {
namespace impl {
//! Simple class that can take an qualifier for which indicies to ignore.
//!
//! Excellent for Brownian bridge where we do not want to set the boundaries
class Data1DOut {
public:
    Data1DOut(Data1D& data, std::function<bool(int)> acceptor) :
        data(data), acceptor(acceptor)
    {
        // empty
    }

    double& operator()(int x) {
        if (acceptor(x)) {
            return data(x);
        } else {
            return throw_away;
        }
    }
private:
    double throw_away = 42.0;
    Data1D data;
    std::function<bool(int)> acceptor;
};

}
}
