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
        fbmpy::fractional_brownian_bridge_1d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian motion in 1D.\n\n"
        "WARNING: EXPERIMENTAL FEATURE. CHECK SOURCE CODE BEFORE USING\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size nx\n"
        "\n"
        ":return: a (nx+1) fractional Brownian motion");

    boost::python::def("fractional_brownian_motion_2d",
        fbmpy::fractional_brownian_bridge_2d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian motion in 2D (or a variant of it).\n\n"
        "WARNING: EXPERIMENTAL FEATURE. CHECK SOURCE CODE BEFORE USING\n\n"
        "WARNING: ZERO ON UPPER AND RIGHT SIDE\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size nx**2\n"
        "\n"
        ":return: a (nx+1) fractional Brownian motion");
}
