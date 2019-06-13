#include "fbmpy/fbmpy.hpp"


BOOST_PYTHON_MODULE(fbmpy) {
    Py_Initialize();
    boost::python::numpy::initialize();
    boost::python::def("generate_fractional_brownian_bridge", fbmpy::generate_fractional_brownian_bridge);
}
