
#include <boost/test/unit_test.hpp>
#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>

BOOST_AUTO_TEST_SUITE(FBM3DTests)

BOOST_AUTO_TEST_CASE(BridgeZero3D) {
    const int N = 64;
    auto X = fbm::generate_normal_random((N + 1) * (N + 1) * (N + 1));

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

BOOST_AUTO_TEST_SUITE_END()
