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

TEST(StringTest, Split)
{
	std::vector<std::string> expect
	{
		"",
		"abc",
		"def",
		"ghi",
		"jkl"
	};
	std::string str = ",abc,def,ghi,jkl";

	std::vector<std::string> actual = XYZCore::StringOper::Split(str, ",");

	EXPECT_EQ(expect, actual);
}

TEST(StringTest, Split_NotFound)
{
	std::vector<std::string> expect;

	std::string str = ",abc,def,ghi,jkl";

	std::vector<std::string> actual = XYZCore::StringOper::Split(str, ".");

	EXPECT_EQ(expect, actual);
}

TEST(StringTest, CutEnd)
{
	std::string expect = "0.1";
	std::string s = "0.1000000";

	XYZCore::StringOper::CutEnd(s, '0');

	EXPECT_EQ(expect, s);
}

TEST(StringTest, CutEnd_All)
{
	std::string expect = "";
	std::string s = "0000000";

	XYZCore::StringOper::CutEnd(s, '0');

	EXPECT_EQ(expect, s);
}

TEST(StringTest, CutEnd_Nothing)
{
	std::string expect = "0000000.1";
	std::string s = "0000000.1";

	XYZCore::StringOper::CutEnd(s, '0');

	EXPECT_EQ(expect, s);
}