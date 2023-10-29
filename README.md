# StaticStringMap

A compile time static string map for C++20 or above.

This nifty little library offers the class `static_string_map`, which is a class that can store a string to string mapping
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
