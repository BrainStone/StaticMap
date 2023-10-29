#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include <utility>

template <std::size_t N, typename C = char>
class static_string_map {
public:
	using str_t = std::basic_string_view<C>;
	using entry_t = std::pair<str_t, str_t>;
	using map_t = std::array<entry_t, N>;
	using it_t = typename map_t::const_iterator;
	using find_t = std::optional<str_t>;

	// Mimic std::map's size functions
	static constexpr std::size_t size = N;
	static constexpr std::size_t max_size = size;
	static constexpr bool empty = (size == 0);

private:
	const map_t sorted_map;
	const it_t map_begin;
	const it_t map_end;

	static constexpr map_t sort_map(map_t unsorted_map) {
		std::sort(unsorted_map.begin(), unsorted_map.end());

		return unsorted_map;
	}

public:
	constexpr explicit static_string_map(const map_t& map)
	    : sorted_map{sort_map(map)}, map_begin{sorted_map.cbegin()}, map_end{sorted_map.cend()} {}
	constexpr explicit static_string_map(const entry_t (&&entries)[N]) : static_string_map{std::to_array(entries)} {}

	[[nodiscard]] constexpr find_t find(str_t key) const {
		const it_t result = std::lower_bound(map_begin, map_end, key,
		                                     [](const entry_t& a, const std::string_view& b) { return a.first < b; });

		if ((result != map_end) && (result->first == key)) [[likely]] {
			return std::make_optional(result->second);
		} else {
			return std::nullopt;
		}
	}

	[[nodiscard]] constexpr str_t at(str_t key) const {
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

	[[nodiscard]] constexpr bool contains(str_t key) const {
		return find(key).has_value();
	}

	[[nodiscard]] constexpr str_t operator[](str_t key) const {
		return at(key);
	}
};
