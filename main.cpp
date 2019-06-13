#include <iostream>
#include <vector>

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
}
    

std::vector<double> fbm3d(double H, int nx, const std::vector<double>& X) {
  
  Data3D data(nx+1);

  
  int level_nx = 1;


  while (level_nx < nx) {
    
    int factor = nx / (2*level_nx);
    // We loop through each line segment
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
	  
	  // x
	  data(mid_x, left_y, left_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z))/2.0;

	  // y
	  data(left_x, mid_y, left_z) = (data(left_x, left_y, left_z) + data(left_x, right_y, left_z))/2.0;

	  // z
	  data(left_x, left_y, mid_z) = (data(left_x, left_y, left_z) + data(left_x, left_y, right_z))/2.0;

	}
      }
    }


    // loop through each face
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
	  
	  // x
	  data(mid_x, mid_x, left_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z)
	    + data(left_x, right_y, left_z) + data(right_x, right_y, left_z))/4.0;

	  // y
	  data(mid_x, left_y, mid_z) = (data(left_x, left_y, left_z) + data(right_x, left_y, left_z)
	    data(left_x, left_y, right_z) + data(right_x, left_y, right_z))/4.0;

	  // z
	  data(left_x, mid_y, mid_z) = (data(left_x, left_y, left_z) + data(left_x, right_y, left_z)
	    data(left_x, left_y, right_z) + data(left_x, right_y, right_z))/4.0;
	}
      }
    }

    

    level_nx *= 2;
  }
