#include <iostream>
#include <vector>
#include <cmath>

namespace {
class Data3D {
public:
  Data3D(int nx) :
    data(nx*nx*nx, 0), nx(nx), ny(nx), nz(nx) {
  }

  double& operator()(int x, int y, int z) {
    return data[z*nx*ny+y*nx+x];
  }


  std::vector<double> data;

  double nx, ny, nz;
};


class VarianceFBM {
public:
  VarianceFBM(const std::vector<double>& X, int nx, double H) : X(X), nx(nx), ny(ny), nz(nz), H(H) {
  }
  
  double operator()(int x, int y, int z, int level) const {
    return variancefBm(level)*X[z*nx*ny + y*nx + x];
  }

  double variancefBm(int level) const {
    return std::sqrt((1.0-std::pow(2.0, (2*H-2))/(std::pow(2, (2*level*H)))));
  }

private:
  std::vector<double> X;
  int nx, ny, nz;
  double H;
};

  }

std::vector<double> fbm3d(double H, int nx, const std::vector<double>& X) {
  
  Data3D data(nx+1);

  VarianceFBM variance(X, nx+1, H);
  
  int level_nx = 1;


  int level = 1;
  while (level_nx < nx) {
    
    int factor = nx / (2*level_nx);

    for (int z = 0; z < level_nx; ++z) {
      for (int y = 0; y < level_nx; ++y) {
	for (int x = 0; x < level_nx; ++z) {
	  int mid_x = factor*(2*x+1);
	  int left_x = factor*2*x;
	  int right_x = factor*2*(x+1);

	  int mid_y = factor*(2*y+1);
	  int left_y = factor*2*y;
	  int right_y = factor*2*(y+1);

	  int mid_z = factor*(2*z+1);
	  int left_z = factor*2*z;
	  int right_z = factor*2*(z+1);

	  // LINE SEGMENTS
	  // x
	  data(mid_x, left_y, left_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z))/2.0
	    + variance(mid_x, left_y, left_z, level);

	  // y
	  data(left_x, mid_y, left_z) = (data(left_x, left_y, left_z) + data(left_x, right_y, left_z))/2.0
	    + variance(left_x, mid_y, left_z, level);

	  // z
	  data(left_x, left_y, mid_z) = (data(left_x, left_y, left_z) + data(left_x, left_y, right_z))/2.0
	    + variance(left_x, left_y, mid_z, level);


	  
	  // SIDES 
	  // x
	  data(mid_x, mid_x, left_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z)
	    + data(left_x, right_y, left_z) + data(right_x, right_y, left_z))/4.0
	    + variance(mid_x, mid_y, left_z, level);

	  // y
	  data(mid_x, left_y, mid_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z)
	    + data(left_x, left_y, right_z) + data(right_x, left_y, right_z))/4.0
	    + variance(mid_x, left_y, mid_z, level);

	  // z
	  data(left_x, mid_y, mid_z) = (data(left_x, left_y, left_z) + data(left_x, right_y, left_z)
	    + data(left_x, left_y, right_z) + data(left_x, right_y, right_z))/4.0
	    + variance(left_x, mid_y, mid_z, level);


	  // CENTER POINT
	  data(mid_x, mid_y, mid_z) = (data(left_x, left_y, left_z) +
				       data(right_x, left_y, left_z) +
				       data(right_x, right_y, left_z) +
				       data(right_x, right_y, right_z) +
				       data(right_x, left_y, right_z) +
				       data(left_x, right_y, left_z) +
				       data(left_x, right_y, right_z) +
				       data(left_x, left_y, right_z))/8.0
	    + variance(mid_x, mid_y, mid_z,level);
	  
	}
      }
    }


    level_nx *= 2;

    level += 1;
  }

  return data.data;
}
 
