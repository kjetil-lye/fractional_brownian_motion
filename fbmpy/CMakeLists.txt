SET(FBM_PYTHON_VERSION "3.7" CACHE STRING "Python version to use")

STRING(REPLACE "." "" FBM_PYTHON_VERSION_PURE ${FBM_PYTHON_VERSION})
MARK_AS_ADVANCED(FBM_PYTHON_VERSION_PURE)

find_package(Python ${FBMPY_PYTHON_VERSION} REQUIRED COMPONENTS Development)
find_package(Boost REQUIRED COMPONENTS python numpy)
add_library(fbmpy SHARED src/fbmpy.cpp)
set_target_properties(fbmpy PROPERTIES PREFIX "")

target_include_directories(fbmpy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(fbmpy Boost::python${FBMPY_PYTHON_VERSION} Boost::numpy${FBMPY_PYTHON_VERSION} fbm Python::Python)
