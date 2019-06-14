#pragma once


namespace fbm {
  namespace impl {
    template<class X>
    bool is_power_of_two(X x) {
      if (x==X(0)) {
	return false;
      }
      // http://www.graphics.stanford.edu/~seander/bithacks.html
      return (x & (x - 1)) == 0;
    }
  }
}
