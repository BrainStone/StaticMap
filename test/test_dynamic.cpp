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
	const std::string_view hello = map["hello"];
	const std::string_view foo = map["foo"];

	EXPECT_EQ(hello, "world");
	EXPECT_EQ(foo, "bar");
}

TEST(TestDynamic, InvalidAccess) {
	EXPECT_THROW(map["hi"], std::out_of_range);
}
