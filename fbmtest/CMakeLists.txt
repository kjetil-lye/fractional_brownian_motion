find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_executable(fbmtest
    src/test_fbm.cpp
    src/test_fbm_1d.cpp
    src/test_fbb_1d.cpp
    src/test_fbb_2d.cpp
    src/test_fbb_3d.cpp)
target_compile_features(fbmtest PUBLIC cxx_std_11)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(fbmtest PRIVATE -Wall -Wextra -Wpedantic -Wno-disabled-macro-expansion)
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(fbmtest PRIVATE -Wall -Wextra -Wpedantic)#disabled-macro-expansion)
endif()
target_compile_definitions(fbmtest PUBLIC -DBOOST_TEST_DYN_LINK)
target_link_libraries(fbmtest Boost::unit_test_framework fbm)
