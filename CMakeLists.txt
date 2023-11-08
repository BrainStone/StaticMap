cmake_minimum_required(VERSION 3.16)
project(static_map CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

###############################################################################
## testing ####################################################################
###############################################################################

option(BUILD_STATIC_MAP_TESTS "Build static_map tests" ON)
if (BUILD_STATIC_MAP_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()
