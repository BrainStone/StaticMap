#include "static_map.hpp"

template<std::size_t N, typename C = char>
using static_string_map = static_map<std::basic_string_view<C>, std::basic_string_view<C>, N>;
