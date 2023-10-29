#include <algorithm>
#include <array>
#include <string_view>
#include <utility>

template <std::size_t N, typename C = char>
class static_string_map {
public:
	using str_t = std::basic_string_view<C>;
	using entry_t = std::pair<str_t, str_t>;
	using map_t = std::array<entry_t, N>;

private:
	const map_t sorted_map;

	static constexpr map_t sort_map(map_t unsorted_map) {
		std::sort(unsorted_map.begin(), unsorted_map.end());

		return unsorted_map;
	}

public:
	constexpr explicit static_string_map(const map_t& map) : sorted_map{sort_map(map)} {}
	constexpr explicit static_string_map(const entry_t (&&entries)[N]) : static_string_map{std::to_array(entries)} {}
	constexpr explicit static_string_map(const entry_t (&entries)[N]) : static_string_map{std::to_array(entries)} {}

	[[nodiscard]] constexpr str_t get(str_t key) const {
		const typename map_t::const_iterator begin = sorted_map.cbegin();
		const typename map_t::const_iterator end = sorted_map.end();

		const typename map_t::const_iterator result =
		    std::lower_bound(begin, end, key, [](const entry_t& a, const std::string_view& b) { return a.first < b; });

		if ((result != end) && (result->first == key)) {
			// Found key
			return result->second;
		} else {
			using namespace std::literals::string_literals;
			// Key not found
			throw std::out_of_range{"Key \""s + key.data() + "\" could not be found in the map"};
		}
	}

	constexpr str_t operator[](str_t key) const {
		return get(key);
	}
};
