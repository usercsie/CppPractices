#include <iostream>
#include "gtest/gtest.h"
#include "StringOper.h"
#include "VectorOper.h"

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

TEST(VectorTest, FindString_Found)
{
	int expect = 2;
	std::vector<std::string> elements
	{
		"abcd",
		"aaaaa",
		"bb",
		"dd"
	};

	int actual = XYZCore::VectorOper::FindString(elements, "bb");

	EXPECT_EQ(expect, actual);
}

TEST(VectorTest, FindString_NotFound)
{
	int expect = -1;
	std::vector<std::string> elements
	{
		"abcd",
		"aaaaa",
		"bb",
		"dd"
	};

	int actual = XYZCore::VectorOper::FindString(elements, "cc");

	EXPECT_EQ(expect, actual);
}

TEST(VectorTest, Data)
{
	std::vector<int> elements
	{
		1,
		2,
		3,
		4
	};

	int* d = elements.data();
	d[0] = 100;

	EXPECT_EQ(100, elements[0]);
}