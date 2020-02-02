#include <iostream>
#include "gtest/gtest.h"
#include "StringOper.h"

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

TEST(VectorTest, RemoveCommentsOrEmptyLines)
{
	std::vector<std::string> expect
	{
		"abcd",
		"aaaaa",		
	};
	std::vector<std::string> lines
	{
		"abcd",
		";aaaa",
		"aaaaa",
		"",
		"   ",
		"\n"
	};

	lines.erase(std::remove_if(lines.begin(), lines.end(), [](std::string const &i)
	{
		return XYZCore::StringOper::IsEmptyOrSpace(i) || i.front() == ';';
	}), lines.end());

	EXPECT_EQ(expect, lines);
}
