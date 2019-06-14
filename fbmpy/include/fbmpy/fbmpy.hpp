/* Copyright (c) 2019 Kjetil Olsen Lye, ETH Zurich
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <fbm/fbm.hpp>
namespace fbmpy {

//! Adapter function for fbm::generate_fractional_brownian_bridge
inline boost::python::numpy::ndarray fractional_brownian_bridge_3d(
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


//! Adapter function for fbm::generate_fractional_brownian_bridge
inline boost::python::numpy::ndarray fractional_brownian_bridge_2d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)* (nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_bridge_2d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()));

    return bridge_data;

}


//! Adapter function for fbm::generate_fractional_brownian_bridge
inline boost::python::numpy::ndarray fractional_brownian_bridge_1d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_bridge_1d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()));

    return bridge_data;

}

//! Adapter function for fbm::generate_fractional_brownian_motion
inline boost::python::numpy::ndarray fractional_brownian_motion_1d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_motion_1d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()));

    return bridge_data;

}


//! Adapter function for fbm::generate_fractional_brownian_motion
inline boost::python::numpy::ndarray fractional_brownian_motion_2d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)* (nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_bridge_2d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()),
        false);

    return bridge_data;

}


//! Adapter function for fbm::generate_fractional_brownian_motion
inline boost::python::numpy::ndarray fractional_brownian_motion_3d(
    double H, int nx, const boost::python::numpy::ndarray& X) {
    Py_intptr_t shape[1] = {(nx + 1)* (nx + 1)* (nx + 1)};
    auto bridge_data = boost::python::numpy::zeros(1, shape,
            boost::python::numpy::dtype::get_builtin<double>());

    fbm::fractional_brownian_bridge_3d(reinterpret_cast<double*>
        (bridge_data.get_data()),
        H,
        nx,
        reinterpret_cast<const double*>(X.get_data()),
        false);

    return bridge_data;

}
}
