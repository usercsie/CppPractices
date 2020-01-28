#include <iostream>
#include <sstream>
#include "gtest/gtest.h"

TEST(StringTest, Format)
{
	int n = 10;
	std::string s = "abc";

	std::ostringstream ss;
	ss << "D:\\ImgOut\\" << n << s << ".bmp";
	std::string actual = ss.str();

	std::string expect = "D:\\ImgOut\\10abc.bmp";
	EXPECT_EQ(expect, actual);	
}

TEST(StringTest, string2wstring)
{
	std::string s = "abc";

	std::wstring ws(s.begin(), s.end());

	EXPECT_EQ(L"abc", ws);
}
