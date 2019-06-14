#pragma once
#include <random>
#include <exception>
#include <sstream>

#define FBM_ASSERT_NON_NEGATIVE(x) { \
    if(x<0) {\
        std::stringstream message; \
        message << "The can generate for a non negativ number of elements.\n"\
                << "Given: " << x << " (variable "<< #x <<")\n\n"\
<< "In " << __FILE__ << " at " << __LINE__ << "\n"; \
    throw std::runtime_error(message.str().c_str());\
} \
}
namespace fbm {
inline std::vector<double> generate_normal_random(int number_of_elements) {
    FBM_ASSERT_NON_NEGATIVE(number_of_elements);
    std::vector<double> random_numbers(size_t(number_of_elements), 0);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (auto& d : random_numbers) {
        d = distribution(generator);
    }

    return random_numbers;
}
}

#undef FBM_ASSERT_GREATER_THAN_ZERO
