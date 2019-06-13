SET(FBM_PYTHON_VERSION "3.7" CACHE STRING "Python version to use")

STRING(REPLACE "." "" FBM_PYTHON_VERSION_PURE ${FBM_PYTHON_VERSION})
MARK_AS_ADVANCED(FBM_PYTHON_VERSION_PURE)

find_package(Python ${FBM_PYTHON_VERSION} REQUIRED COMPONENTS Development)
find_package(Boost REQUIRED COMPONENTS python${FBM_PYTHON_VERSION_PURE} numpy${FBM_PYTHON_VERSION_PURE})

add_library(fbmpy SHARED src/fbmpy.cpp)

target_compile_features(fbmpy PUBLIC cxx_std_11)
set_target_properties(fbmpy PROPERTIES PREFIX "")

target_include_directories(fbmpy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(fbmpy Boost::python${FBM_PYTHON_VERSION_PURE} Boost::numpy${FBM_PYTHON_VERSION_PURE} fbm Python::Python)
