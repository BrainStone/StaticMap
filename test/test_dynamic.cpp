#include "gtest/gtest.h"
#include "static_string_map.hpp"

const static_string_map map{{{"hello", "world"}, {"foo", "bar"}}};

TEST(TestDynamic, Initialization) {
	const static_string_map local_map{{{"hello", "world"}, {"foo", "bar"}}};

	EXPECT_EQ(local_map.size, 2);
	EXPECT_EQ(local_map.max_size, local_map.size);
	EXPECT_FALSE(local_map.empty);

	EXPECT_EQ(map.size, 2);
	EXPECT_EQ(local_map.max_size, local_map.size);
	EXPECT_FALSE(map.empty);
}

TEST(TestDynamic, ValidAccess) {
	EXPECT_EQ(map["hello"], "world");
	EXPECT_EQ(map["foo"], "bar");
}

TEST(TestDynamic, InvalidAccess) {
	// Casting to void to disable the warning about nodiscard
	EXPECT_THROW((void)map["hi"], std::out_of_range);
}

TEST(TestDynamic, Contains) {
	EXPECT_TRUE(map.contains("hello"));
	EXPECT_FALSE(map.contains("hi"));
}

TEST(TestDynamic, Find) {
	const auto hello = map.find("hello");
	const auto hi = map.find("hi");

	EXPECT_TRUE(hello);
	EXPECT_EQ(*hello, "world");

	EXPECT_FALSE(hi);
}
