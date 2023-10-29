#include "gtest/gtest.h"
#include "static_string_map.hpp"

constexpr static_string_map map{{{"hello", "world"}, {"foo", "bar"}}};

TEST(TestConstexpr, Initialization) {
	constexpr static_string_map local_map{{{"hello", "world"}, {"foo", "bar"}}};

	EXPECT_EQ(local_map.size, 2);
	EXPECT_EQ(map.size, 2);
}

TEST(TestConstexpr, Access) {
	constexpr std::string_view hello = map["hello"];
	constexpr std::string_view foo = map["foo"];

	EXPECT_EQ(hello, "world");
	EXPECT_EQ(foo, "bar");
}
