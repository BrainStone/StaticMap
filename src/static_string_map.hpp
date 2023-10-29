#ifndef STATIC_MAP__STATIC_STRING_MAP_HPP
#define STATIC_MAP__STATIC_STRING_MAP_HPP

#include "static_map.hpp"

template <std::size_t N, typename C = char>
using static_string_map = static_map<std::basic_string_view<C>, std::basic_string_view<C>, N>;

#endif  // #ifndef STATIC_MAP__STATIC_STRING_MAP_HPP
