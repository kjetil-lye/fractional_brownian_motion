find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_executable(fbmtest
    src/test_fbm.cpp
    src/test_fbm_1d.cpp
    src/test_fbm_2d.cpp
    src/test_fbm_3d.cpp)
target_compile_features(fbmtest PUBLIC cxx_std_11)
target_compile_definitions(fbmtest PUBLIC -DBOOST_TEST_DYN_LINK)
target_link_libraries(fbmtest Boost::unit_test_framework fbm)
