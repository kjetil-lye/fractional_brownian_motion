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

#include "fbmpy/fbmpy.hpp"


BOOST_PYTHON_MODULE(fbmpy) {
    Py_Initialize();
    boost::python::numpy::initialize();
    boost::python::def("fractional_brownian_bridge_3d",
        fbmpy::fractional_brownian_bridge_3d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian bridge in 3D.\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size (nx-1)**3\n"
        "\n"
        ":return: a (nx+1, nx+1, nx+1) fractional Brownian bridge");

    boost::python::def("fractional_brownian_bridge_2d",
        fbmpy::fractional_brownian_bridge_2d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian bridge in 2D.\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size (nx-1)**2\n"
        "\n"
        ":return: a (nx+1, nx+1) fractional Brownian bridge");

    boost::python::def("fractional_brownian_bridge_1d",
        fbmpy::fractional_brownian_bridge_1d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian bridge in 1D.\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size (nx-1)\n"
        "\n"
        ":return: a (nx+1) fractional Brownian bridge");

    boost::python::def("fractional_brownian_motion_1d",
        fbmpy::fractional_brownian_motion_1d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian motion in 1D.\n\n"
        "WARNING: EXPERIMENTAL FEATURE. CHECK SOURCE CODE BEFORE USING\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size nx\n"
        "\n"
        ":return: a (nx+1) fractional Brownian motion");

    boost::python::def("fractional_brownian_motion_2d",
        fbmpy::fractional_brownian_motion_2d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian motion in 2D (or a variant of it).\n\n"
        "WARNING: EXPERIMENTAL FEATURE. CHECK SOURCE CODE BEFORE USING\n\n"
        "WARNING: ZERO ON UPPER AND RIGHT SIDE\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size nx**2\n"
        "\n"
        ":return: a (nx+1) fractional Brownian motion");

    boost::python::def("fractional_brownian_motion_3d",
        fbmpy::fractional_brownian_motion_3d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian motion in 3D (or a variant of it).\n\n"
        "WARNING: EXPERIMENTAL FEATURE. CHECK SOURCE CODE BEFORE USING\n\n"
        "WARNING: ZERO ON UPPER AND RIGHT SIDE\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size nx**3\n"
        "\n"
        ":return: a (nx+1) fractional Brownian motion");

}
