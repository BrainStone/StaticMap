#include <algorithm>
#include <array>
#include <concepts>
#include <optional>
#include <string_view>
#include <utility>

template <std::totally_ordered K, typename V, std::size_t N>
class static_map {
public:
	using key_t = K;
	using value_t = V;
	using entry_t = std::pair<key_t, value_t>;
	using map_t = std::array<entry_t, N>;
	using it_t = typename map_t::const_iterator;
	using find_t = std::optional<V>;

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
	const map_t sorted_map;

	static constexpr map_t sort_map(map_t unsorted_map) {
		std::sort(unsorted_map.begin(), unsorted_map.end());

		return unsorted_map;
	}

public:
	constexpr explicit static_map(const map_t& map) : sorted_map{sort_map(map)} {}
	constexpr explicit static_map(const entry_t (&&entries)[N]) : static_map{std::to_array(entries)} {}

	[[nodiscard]] constexpr find_t find(key_t key) const {
		const it_t begin = sorted_map.cbegin();
		const it_t end = sorted_map.cend();

		const it_t result =
		    std::lower_bound(begin, end, key, [](const entry_t& a, const std::string_view& b) { return a.first < b; });

		if ((result != end) && (result->first == key)) [[likely]] {
			return std::make_optional(result->second);
		} else {
			return std::nullopt;
		}
	}

	[[nodiscard]] constexpr value_t at(key_t key) const {
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

	[[nodiscard]] constexpr bool contains(key_t key) const {
		return find(key).has_value();
	}

	[[nodiscard]] constexpr value_t operator[](key_t key) const {
		return at(key);
	}
};
