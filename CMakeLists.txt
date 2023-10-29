cmake_minimum_required(VERSION 3.16)
project(static_string_map CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

###############################################################################
## testing ####################################################################
###############################################################################

enable_testing()
include(GoogleTest)
add_subdirectory(test)
