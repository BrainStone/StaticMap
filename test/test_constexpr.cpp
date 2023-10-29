#include "gtest/gtest.h"
#include "static_string_map.hpp"

constexpr static_string_map map{{{"hello", "world"}, {"foo", "bar"}}};

TEST(TestConstexpr, Initialization) {
	constexpr static_string_map local_map{{{"hello", "world"}, {"foo", "bar"}}};

	EXPECT_EQ(local_map.size, 2);
	EXPECT_EQ(local_map.max_size, local_map.size);
	EXPECT_FALSE(local_map.empty);

	EXPECT_EQ(map.size, 2);
	EXPECT_EQ(local_map.max_size, local_map.size);
	EXPECT_FALSE(map.empty);
}

TEST(TestConstexpr, Access) {
	constexpr std::string_view hello = map["hello"];
	constexpr std::string_view foo = map["foo"];

	EXPECT_EQ(hello, "world");
	EXPECT_EQ(foo, "bar");
}

TEST(TestConstexpr, Contains) {
	constexpr bool hello = map.contains("hello");
	constexpr bool hi = map.contains("hi");

	EXPECT_TRUE(hello);
	EXPECT_FALSE(hi);
}

TEST(TestConstexpr, Find) {
	constexpr auto hello = map.find("hello");
	constexpr auto hi = map.find("hi");

	EXPECT_TRUE(hello);
	EXPECT_EQ(*hello, "world");

	EXPECT_FALSE(hi);
}
