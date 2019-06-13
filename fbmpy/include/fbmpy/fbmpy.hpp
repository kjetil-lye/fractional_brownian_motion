#pragma once
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <fbm/fbm.hpp>
namespace fbmpy {

//! Adapter function for fbm::generate_fractional_brownian_bridge
inline boost::python::numpy::ndarray generate_fractional_brownian_bridge_3d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)* (nx + 1)* (nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_bridge_3d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()));

    return bridge_data;

}
}
