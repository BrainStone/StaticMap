#ifndef STATIC_MAP_STATIC_STRING_MAP_HPP
#define STATIC_MAP_STATIC_STRING_MAP_HPP

#include "static_map.hpp"

template <typename C, std::size_t N>
using static_string_map = static_map<std::basic_string_view<C>, std::basic_string_view<C>, N>;

template <std::size_t N>
constexpr static_string_map<char, N> make_static_string_map(
    const typename static_string_map<char, N>::entry_t (&entries)[N]) {
	return static_string_map<char, N>{entries};
};

template <typename C, std::size_t N>
constexpr static_string_map<C, N> make_static_string_map(
    const typename static_string_map<C, N>::entry_t (&entries)[N]) {
	return static_string_map<C, N>{entries};
};

#endif  // #ifndef STATIC_MAP_STATIC_STRING_MAP_HPP
