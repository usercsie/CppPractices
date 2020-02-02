#include <iostream>
#include <sstream>
#include "gtest/gtest.h"
#include "StringOper.h"

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

TEST(StringTest, TrimStartEnd)
{
	std::string expect = "abc def gh";
	std::string str = " abc def gh ";
	XYZCore::StringOper::Trim(str);

	EXPECT_EQ(expect, str);
}

TEST(StringTest, TrimAll)
{
	std::string expect = "abcdefgh";
	std::string str = " abc def gh ";
	XYZCore::StringOper::TrimAll(str);

	EXPECT_EQ(expect, str);
}

TEST(StringTest, EraseAllSpace)
{
	std::string expect = "abcdefgh";
	std::string str = " abc def gh ";
	XYZCore::StringOper::EraseAll(str, ' ');

	EXPECT_EQ(expect, str);
}

TEST(StringTest, StringIsEmpty)
{
	bool expect = true;
	std::string str = "";

	bool actual = XYZCore::StringOper::IsEmptyOrSpace(str);
	
	EXPECT_EQ(expect, actual);
}

TEST(StringTest, StringIsSpace)
{
	bool expect = true;
	std::string str = "  ";

	bool actual = XYZCore::StringOper::IsEmptyOrSpace(str);

	EXPECT_EQ(expect, actual);
}

TEST(StringTest, StringIsNewLine)
{
	bool expect = true;
	std::string str = "\n";

	bool actual = XYZCore::StringOper::IsEmptyOrSpace(str);

	EXPECT_EQ(expect, actual);
}

TEST(StringTest, StringIsTab)
{
	bool expect = true;
	std::string str = "\t";

	bool actual = XYZCore::StringOper::IsEmptyOrSpace(str);

	EXPECT_EQ(expect, actual);
}

TEST(StringTest, StringIsSpace_Return_False)
{
	bool expect = false;
	std::string str = " a  ";

	bool actual = XYZCore::StringOper::IsEmptyOrSpace(str);

	EXPECT_EQ(expect, actual);
}