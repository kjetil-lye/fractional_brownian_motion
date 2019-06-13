#include "fbmpy/fbmpy.hpp"


BOOST_PYTHON_MODULE(fbmpy) {
    Py_Initialize();
    boost::python::numpy::initialize();
    boost::python::def("generate_fractional_brownian_bridge_3d",
        fbmpy::generate_fractional_brownian_bridge_3d,
        boost::python::args("H", "nx", "X"),
        "Generate a fractional Brownian bridge in 3D.\n\n"
        "   :param H: Hurst index\n"
        "   :param nx: number of cells in each dimension\n"
        "   :param X: normal random vector of size (nx+1)**3\n"
        "\n"
        ":return: a (nx+1, nx+1, nx+1) fractional Brownian bridge");
}
