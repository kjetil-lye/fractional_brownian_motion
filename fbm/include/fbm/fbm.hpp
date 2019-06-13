#pragma once
#include <vector>
namespace fbm {
std::vector<double> fractional_brownian_bridge_3d(double H, int nx, const std::vector<double>& X);
}
