[![Build Status](https://travis-ci.org/kjetil-lye/fractional_brownian_motion.svg?branch=master)](https://travis-ci.org/kjetil-lye/fractional_brownian_motion)
# Fractional Brownian motion

A *header only* C++ library for generating fractional Brownian motion in 1D, 2D and 3D (the latter two are technically variants of a fractional Brownian bridge).

We focus on fast implementation, therefore, we can *only generate for lengths that are a power of 2*.

This library is mainly used from within the [Alsvinn](https://alsvinn.github.io/alsvinn) simulator. 

Also comes with a Python library (requires```boost::python``` and ```boost::numpy```).

## Requirements

  * A C++11 compatible compiler (tested with GCC and Clang)
  * [cmake](https://cmake.org) >= 3.10.0 (optional)
  * [boost](https://www.boost.org) >= 1.67.0 (optional) only for python and tests
  * [python](https://www.python.org) (optional) for python bindings
  * [doxygen](https://doxygen.nl) (optional) for documentation

## Running from Python
Make sure the folder ```fbmpy``` from the build folder is in your ```PYTHONPATH```. Then from Python you can do something like:

```python
import fbmpy
import numpy as np
import matplotlib.pyplot as plt

# Plain old Brownian motion
Hurst_index = 0.5

N = 128
X = np.random.normal(0, 1, N)
d = fbmpy.fractional_brownian_motion_1d(Hurst_index, N, X)
x = np.linspace(0, 1, N+1)
plt.plot(x, d)
plt.show()
```
