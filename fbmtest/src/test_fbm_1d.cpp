

#include <boost/test/unit_test.hpp>
#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>

BOOST_AUTO_TEST_SUITE(FBM1DTests)

BOOST_AUTO_TEST_CASE(BridgeZero1D) {
    const int N = 128;
    auto X = fbm::generate_normal_random(N - 1);

    auto fBm = fbm::fractional_brownian_bridge_1d(0.5, N, X);

    BOOST_TEST(N + 1 == fBm.size());
    BOOST_TEST(0.0 == fBm[0]);
    BOOST_TEST(0.0 == fBm[N]);
}


BOOST_AUTO_TEST_CASE(SmallSizeTwo) {
    // Check that we can create small sizes
    int N = 2;
    auto X = fbm::generate_normal_random((N - 1));

    auto fBm = fbm::fractional_brownian_bridge_1d(0.5, N, X);

    BOOST_TEST(fBm.size() == 3);
}

BOOST_AUTO_TEST_CASE(SmallSizeOne) {
    // Check that we can create small sizes
    int N = 1;
    auto X = fbm::generate_normal_random((N - 1));

    auto fBm = fbm::fractional_brownian_bridge_1d(0.5, N, X);

    BOOST_TEST(fBm.size() == 2);

    for (auto d : fBm) {
        BOOST_TEST(d == 0);
    }


}

BOOST_AUTO_TEST_CASE(ThrowsOnNonePowerOfTwo) {
    std::vector<int> non_powers = {3, 5, 6, 12};

    for (auto non_power : non_powers) {
        auto X = fbm::generate_normal_random((non_power - 1));
        //Boost check throw wouldn't work

        try {
            auto fBm = fbm::fractional_brownian_bridge_1d(0.5, non_power, X);
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
            auto fBm = fbm::fractional_brownian_bridge_1d(0.5, non_positive, X);
        } catch (std::runtime_error e) {
            continue;
        }

        BOOST_TEST(false);
    }
}


BOOST_AUTO_TEST_CASE(HoelderExponent, * boost::unit_test::tolerance(0.3)) {
    std::vector<double> Hs = {0.5, 0.7};

    for (auto H : Hs) {
        // Checks that we get a Holder exponent of roughly H
        std::vector<int> resolutions = {4096, 2 * 4096, 4 * 4096, 8 * 4096};

        const int N = resolutions.back();
        auto X = fbm::generate_normal_random(N - 1);

        for (auto resolution : resolutions) {
            auto fBm = fbm::fractional_brownian_bridge_1d(H, resolution, X);

            double average_alpha = 0.0;

            for (int i = 0; i < resolution; ++i) {
                const double diff_x = 1.0 / resolution;
                const double diff_fx = std::abs(fBm[i + 1] - fBm[i]);

                const double alpha = std::log(diff_fx) / std::log(diff_x);

                average_alpha += alpha;
            }

            average_alpha /= resolution;

            BOOST_TEST(average_alpha == H);
        }
    }
}

BOOST_AUTO_TEST_CASE(Nested) {
    std::vector<int> resolutions = {32, 64, 128, 256, 512};

    const int N = 2 * resolutions.back();
    auto X = fbm::generate_normal_random(N - 1);

    for (auto resolution : resolutions) {

        auto fBm = fbm::fractional_brownian_bridge_1d(0.5, resolution, X);
        auto fBm_fine = fbm::fractional_brownian_bridge_1d(0.5, 2 * resolution, X);

        for (int i = 0; i < resolution; ++i) {
            BOOST_TEST(fBm[i] == fBm_fine[2 * i]);
        }
    }

}

BOOST_AUTO_TEST_SUITE_END()
