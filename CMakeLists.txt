cmake_minimum_required(VERSION 3.10.0)
project(fbm CXX)

SET(BUILD_CLI ON CACHE BOOL "Build CLI app")

add_subdirectory(fbm)

if (BUILD_CLI)
   add_subdirectory(cli)
endif()
