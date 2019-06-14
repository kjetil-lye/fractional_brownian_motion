
#include <boost/test/unit_test.hpp>
#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>

BOOST_AUTO_TEST_SUITE(FBM3DTests)

BOOST_AUTO_TEST_CASE(BridgeZero3D) {
    const int N = 64;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_3d(0.5, N, X);

    BOOST_TEST((N + 1) * (N + 1) * (N + 1) == fBm.size());

    for (size_t i = 0; i < N + 1; ++i) {
        for (size_t j = 0; j < N + 1; ++j) {
            BOOST_TEST(0.0 == fBm[i + (N + 1)*j]);
            BOOST_TEST(0.0 == fBm[i + (N + 1)*j + N * (N + 1) * (N + 1)]);

            BOOST_TEST(0.0 == fBm[i + (N + 1) * (N + 1)*j]);
            BOOST_TEST(0.0 == fBm[i + N * (N + 1)]);

            BOOST_TEST(0.0 == fBm[i * (N + 1) + (N + 1) * (N + 1)*j]);
            BOOST_TEST(0.0 == fBm[i * (N + 1) + N]);
        }
    }
}

BOOST_AUTO_TEST_CASE(SmallSizeTwo) {
    // Check that we can create small sizes
    int N = 2;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_3d(0.5, N, X);

    BOOST_TEST(fBm.size() == 27);


}

BOOST_AUTO_TEST_CASE(SmallSizeOne) {
    // Check that we can create small sizes
    int N = 1;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_3d(0.5, N, X);

    BOOST_TEST(fBm.size() == 8);

    for (auto d : fBm) {
        BOOST_TEST(d == 0);
    }


}

BOOST_AUTO_TEST_CASE(Nested) {
    // Check that is is indeed just nested
    std::vector<int> resolutions = {8, 16, 32, 64};


    const int N = 2 * resolutions.back();
    auto X = fbm::generate_normal_random((N - 1) * (N - 1) * (N - 1));

    for (auto resolution : resolutions) {

        auto fBm = fbm::fractional_brownian_bridge_3d(0.5, resolution, X);
        auto fBm_fine = fbm::fractional_brownian_bridge_3d(0.5, 2 * resolution, X);

        for (int i = 0; i < resolution; ++i) {
            for (int j = 0; j < resolution; ++j) {
                for (int k = 0; k < resolution; ++k) {

                    BOOST_TEST(fBm[i * (resolution + 1) * (resolution + 1) + j *
                            (resolution + 1) + k] == fBm_fine[2 * i *
                            (2 * resolution + 1) * (2 * resolution + 1) + 2 * j * (2 * resolution + 1) +
                            2 * k]);
                }
            }
        }
    }

}


BOOST_AUTO_TEST_CASE(ThrowsOnNonePowerOfTwo) {
    std::vector<int> non_powers = {3, 5, 6, 12};

    for (auto non_power : non_powers) {
        auto X = fbm::generate_normal_random((non_power - 1));
        //Boost check throw wouldn't work

        try {
            auto fBm = fbm::fractional_brownian_bridge_3d(0.5, non_power, X);
        } catch (std::runtime_error e) {
            continue;
        }

        BOOST_TEST(false);
    }
}

BOOST_AUTO_TEST_CASE(ThrowsOnNonPositive) {
    std::vector<int> non_positives = {-10, -4, 0};
    auto X = fbm::generate_normal_random((10 - 1));

    for (auto non_positive : non_positives) {

        //Boost check throw wouldn't work

        try {
            auto fBm = fbm::fractional_brownian_bridge_3d(0.5, non_positive, X);
        } catch (std::runtime_error e) {
            continue;
        }

        BOOST_TEST(false);
    }
}

BOOST_AUTO_TEST_SUITE_END()
