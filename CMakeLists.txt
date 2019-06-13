cmake_minimum_required(VERSION 3.10.0)
project(fbm CXX)

SET(FBM_BUILD_CLI ON CACHE BOOL "Build CLI app")
SET(FBM_BUILD_PYTHON ON CACHE BOOL "Build python module")


add_subdirectory(fbm)

if (FBM_BUILD_CLI)
   add_subdirectory(cli)
endif()

if(FBM_BUILD_PYTHON)
    add_subdirectory(fbmpy)
endif()
