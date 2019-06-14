/* Copyright (c) 2019 Kjetil Olsen Lye, ETH Zurich
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <boost/test/unit_test.hpp>
#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>

BOOST_AUTO_TEST_SUITE(FBB2DTests)


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

BOOST_AUTO_TEST_CASE(BridgeZero2DNotSidesToZero) {
    const int N = 64;
    auto X = fbm::generate_normal_random((N) * (N));

    auto fBm = fbm::fractional_brownian_bridge_2d(0.5, N, X, false);

    BOOST_TEST((N + 1) * (N + 1) == fBm.size());

    BOOST_TEST(fBm[0] == 0);
    BOOST_TEST(fBm[N] == 0);
    BOOST_TEST(fBm[N * (N + 1)] == 0);
    BOOST_TEST(fBm[N * (N + 1) + N] == 0);

    for (size_t i = 1; i < N; ++i) {
        BOOST_TEST(0.0 != fBm[i]);
        BOOST_TEST(0.0 != fBm[(N + 1) * i]);
    }
}



BOOST_AUTO_TEST_CASE(SmallSizeTwo) {
    // Check that we can create small sizes
    int N = 2;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_2d(0.5, N, X);

    BOOST_TEST(fBm.size() == 9);


}

BOOST_AUTO_TEST_CASE(SmallSizeOne) {
    // Check that we can create small sizes
    int N = 1;
    auto X = fbm::generate_normal_random((N - 1) * (N - 1));

    auto fBm = fbm::fractional_brownian_bridge_2d(0.5, N, X);

    BOOST_TEST(fBm.size() == 4);

    for (auto d : fBm) {
        BOOST_TEST(d == 0);
    }


}

BOOST_AUTO_TEST_CASE(Nested) {

    //return;
    std::vector<int> resolutions = {8, 16, 32, 64, 128};


    const int N = 2 * resolutions.back();
    auto X = fbm::generate_normal_random((N - 1) * (N - 1));

    for (auto resolution : resolutions) {

        auto fBm = fbm::fractional_brownian_bridge_2d(0.5, resolution, X);
        auto fBm_fine = fbm::fractional_brownian_bridge_2d(0.5, 2 * resolution, X);

        for (int i = 0; i < resolution; ++i) {
            for (int j = 0; j < resolution; ++j) {

                BOOST_TEST(fBm[i * (resolution + 1) + j] == fBm_fine[2 * i *
                        (2 * resolution + 1) + 2 * j]);
            }
        }
    }

}



BOOST_AUTO_TEST_CASE(NestedNotSetSidesToZero) {

    //return;
    std::vector<int> resolutions = {8, 16, 32, 64, 128};


    const int N = 2 * resolutions.back();
    auto X = fbm::generate_normal_random((N) * (N));

    for (auto resolution : resolutions) {

        auto fBm = fbm::fractional_brownian_bridge_2d(0.5, resolution, X, false);
        auto fBm_fine = fbm::fractional_brownian_bridge_2d(0.5, 2 * resolution, X,
                false);

        for (int i = 0; i < resolution; ++i) {
            for (int j = 0; j < resolution; ++j) {

                BOOST_TEST(fBm[i * (resolution + 1) + j] == fBm_fine[2 * i *
                        (2 * resolution + 1) + 2 * j]);
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
            auto fBm = fbm::fractional_brownian_bridge_2d(0.5, non_power, X);
        } catch (std::runtime_error& e) {
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
            auto fBm = fbm::fractional_brownian_bridge_2d(0.5, non_positive, X);
        } catch (std::runtime_error& e) {
            continue;
        }

        BOOST_TEST(false);
    }
}


BOOST_AUTO_TEST_CASE(NonZeroInterior) {
    // We generate a fake random vector with constnat value 1.0
    // This should guarantee that we never get any zero values in the interior.
    const int N = 64;

    std::vector<double> X(N * N, 1);

    auto fBm = fbm::fractional_brownian_bridge_2d(0.5, N, X);

    BOOST_TEST((N + 1) * (N + 1) == fBm.size());

    for (size_t i = 0; i < N + 1; ++i) {
        BOOST_TEST(0.0 == fBm[i]);
        BOOST_TEST(0.0 == fBm[i + N * (N + 1)]);
        BOOST_TEST(0.0 == fBm[(N + 1) * i]);
        BOOST_TEST(0.0 == fBm[(N + 1) * i + N]);

    }

    for (size_t i = 1; i < N; ++i) {
        for (size_t j = 1; j < N; ++j) {
            BOOST_TEST(0.0 != fBm[i + j * (N + 1)]);
        }
    }
}


BOOST_AUTO_TEST_SUITE_END()
