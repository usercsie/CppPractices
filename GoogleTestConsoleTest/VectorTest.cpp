#include <iostream>
#include "gtest/gtest.h"


TEST(VectorTest, stringToByteArray)
{
	std::string str = "abcde";

	std::vector<unsigned char> vec;
	vec.assign(str.begin(), str.end());

	EXPECT_EQ(5, vec.size());

	int start = 97;//a
	for (auto v : vec)
	{		
		EXPECT_EQ(start++, v);
	}
}