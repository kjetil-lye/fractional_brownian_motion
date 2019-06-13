#include "fbm/generate_normal_random.hpp"
#include <random>

namespace fbm {
std::vector<double> generate_normal_random(int number_of_elements) {
    std::vector<double> random_numbers(size_t(number_of_elements), 0);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (auto& d : random_numbers) {
        d = distribution(generator);
    }

    return random_numbers;
}
}
