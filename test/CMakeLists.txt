# Build output setup
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

################################
# Tests
################################
project(${PROJECT_NAME}_test CXX)

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variable `test_sources`
file(GLOB_RECURSE test_sources *.cpp *.hpp)

# Create test executable and let be discoverable
set(DART_ALWAYS_COMPILE_TESTS ON CACHE BOOL "" FORCE)

enable_testing()
add_executable(${PROJECT_NAME} ${test_sources})
gtest_discover_tests(${PROJECT_NAME} XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/reports)

# Link test executable against gtest & gtest_main
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main static_string_map)

# Be very strict with compiling
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /W3 /WX)
    target_link_options(${PROJECT_NAME} PRIVATE /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_link_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif ()
