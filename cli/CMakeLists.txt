add_executable(fbm_cli src/main.cpp)
target_compile_features(fbm_cli PUBLIC cxx_std_11)
target_link_libraries(fbm_cli fbm)
