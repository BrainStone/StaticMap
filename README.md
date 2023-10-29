# StaticStringMap

A compile time static string map for C++20 or above.

This nifty little library offers the class `static_string_map`, which is a class that can store a string to string
mapping
at compile time, including retrieving the values at compile time. The strings in question are `std::string_view` strings
for maximum efficiency.

## Usage Example

```cpp
#include "static_string_map.hpp"

constexpr static_string_map messages{{{"hi", "hi"}, {"foo", "bar"}}};
constexpr std::string_view constexpr_message = messages["foo"]; // Initialized to "bar"
constexpr std::string_view constexpr_message = messages["xxx"]; // Compile error

int main() {
    std::string dynamic_message;
    std::cin >> dynamic_message
    
    std::cout << messages[dynamic_message] << std::endl; // Will either print the corresponding message or throw an exception
}
```

## Using this lib

This is a CMake library, and you can use it as you would any other CMake library. See Instructions further down on how
to use it without CMake too.

### CMake

You can use the `FetchContent` module to let CMake download the lib for you:

```cmake
# Download stomfoolery
include(FetchContent)
FetchContent_Declare(
        static_string_map
        GIT_REPOSITORY https://github.com/BrainStone/StaticStringMap.git
        GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(static_string_map)

# Use static_string_map
project(${PROJECT_NAME} CXX)
target_link_libraries(${PROJECT_NAME} PRIVATE static_string_map)
```

### Without CMake

Essentially you have two options:

- Add `$static_string_map_base_path/src` to your include paths.
- Copy `src/static_string_map.hpp` into an already in use include path.

## Building

First of all there's no actual library to build. The only thing that can be build and executed are the test.  
Now this is a CMake project, so just follow standard build procedure:

```bash
# Build
cmake -B build
cmake --build build

# Run tests
cd build
ctest
```
