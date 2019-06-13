add_library(fbm src/fbm.cpp src/generate_normal_random.cpp)
target_compile_features(fbm PUBLIC cxx_std_11)
target_include_directories(fbm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
