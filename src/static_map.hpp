#ifndef STATIC_MAP__STATIC_MAP_HPP
#define STATIC_MAP__STATIC_MAP_HPP

#include <algorithm>
#include <array>
#include <concepts>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#define STATIC_MAP_TYPEDEFS                      \
public:                                          \
	using key_t = K;                             \
	using value_t = V;                           \
	using entry_t = std::pair<key_t, value_t>;   \
	using map_t = std::array<entry_t, N>;        \
	using it_t = typename map_t::const_iterator; \
	using find_t = std::optional<V>

namespace detail {
// Helper class that stores the actual data and acts differently depending on the properties of K
template <typename K, typename V, std::size_t N>
class storage_impl {};

// K is totally ordered, which means we can sort! This sorts the map/keys on initialization and uses binary search to
// find the values.
template <std::totally_ordered K, typename V, std::size_t N>
class storage_impl<K, V, N> {
	STATIC_MAP_TYPEDEFS;

private:
	const map_t map;

	static constexpr map_t sort_map(map_t unsorted_map) {
		std::sort(unsorted_map.begin(), unsorted_map.end());

		return unsorted_map;
	}

public:
	constexpr explicit storage_impl(const map_t& map) : map{sort_map(map)} {}

	[[nodiscard]] constexpr find_t find(key_t key) const {
		const it_t begin = map.cbegin();
		const it_t end = map.cend();

		const it_t result =
		    std::lower_bound(begin, end, key, [](const entry_t& a, const key_t& b) { return a.first < b; });

		if ((result != end) && (result->first == key)) [[likely]] {
			return std::make_optional(result->second);
		} else {
			return std::nullopt;
		}
	}
};

// K is just equality comparable, which means we can't sort the map/keys. This uses a linear search, which is the best
// we can do for an unsorted list of data. This essentially acts as a fallback.
template <std::equality_comparable K, typename V, std::size_t N>
class storage_impl<K, V, N> {
	STATIC_MAP_TYPEDEFS;

private:
	const map_t map;

public:
	constexpr explicit storage_impl(const map_t& map) : map{map} {}

	[[nodiscard]] constexpr find_t find(const key_t& key) const {
		const it_t begin = map.cbegin();
		const it_t end = map.cend();

		const it_t result = std::find_if(begin, end, [&key](const entry_t& a) { return a.first == key; });

		if (result != end) [[likely]] {
			return std::make_optional(result->second);
		} else {
			return std::nullopt;
		}
	}
};
}  // namespace detail

template <std::equality_comparable K, typename V, std::size_t N>
class static_map {
	STATIC_MAP_TYPEDEFS;

public:
	// Mimic std::map's size functions
	static constexpr std::size_t size() {
		return N;
	}

	static constexpr std::size_t max_size() {
		return size();
	}

	static constexpr bool empty() {
		return size() == 0;
	};

private:
	const detail::storage_impl<K, V, N> map;

	static constexpr map_t sort_map(map_t unsorted_map) {
		std::sort(unsorted_map.begin(), unsorted_map.end());

		return unsorted_map;
	}

public:
	constexpr explicit static_map(const map_t& map) : map{map} {}
	constexpr explicit static_map(const entry_t (&&entries)[N]) : static_map{std::to_array(entries)} {}

	[[nodiscard]] constexpr find_t find(const key_t& key) const {
		return map.find(key);
	}

	[[nodiscard]] constexpr value_t at(const key_t& key) const {
		const find_t search_result = find(key);

		if (search_result) [[likely]] {
			// Found key
			return *search_result;
		} else {
			using namespace std::literals::string_literals;
			// Key not found
			throw std::out_of_range{"Key \""s + key.data() + "\" could not be found in the map"};
		}
	}

	[[nodiscard]] constexpr bool contains(const key_t& key) const {
		return find(key).has_value();
	}

	[[nodiscard]] constexpr value_t operator[](const key_t& key) const {
		return at(key);
	}
};

// Cleanup just in case
#undef STATIC_MAP_TYPEDEFS

#endif #ifndef STATIC_MAP__STATIC_MAP_HPP
