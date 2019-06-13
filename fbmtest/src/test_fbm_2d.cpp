
#include <boost/test/unit_test.hpp>
#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>

BOOST_AUTO_TEST_SUITE(FBM2DTests)


BOOST_AUTO_TEST_CASE(BridgeZero2D) {
    const int N = 64;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_2d(0.5, N, X);

    BOOST_TEST((N + 1) * (N + 1) == fBm.size());

    for (size_t i = 0; i < N + 1; ++i) {
        BOOST_TEST(0.0 == fBm[i]);
        BOOST_TEST(0.0 == fBm[i + N * (N + 1)]);
        BOOST_TEST(0.0 == fBm[(N + 1) * i]);
        BOOST_TEST(0.0 == fBm[(N + 1) * i + N]);

    }
}

BOOST_AUTO_TEST_CASE(Nested) {

    //return;
    std::vector<int> resolutions = {8};
    //, 32, 64, 128


    const int N = 2 * resolutions.back();
    auto X = fbm::generate_normal_random((N - 1) * (N - 1));

    for (auto resolution : resolutions) {

        auto fBm = fbm::fractional_brownian_bridge_2d(0.5, resolution, X);
        auto fBm_fine = fbm::fractional_brownian_bridge_2d(0.5, 2 * resolution, X);

        for (int i = 0; i < resolution; ++i) {
            for (int j = 0; j < resolution; ++j) {
                //BOOST_TEST(fBm[i * resolution + j] == fBm_fine[2 * i * N + 2 * j]);
            }
        }
    }

}

BOOST_AUTO_TEST_SUITE_END()
