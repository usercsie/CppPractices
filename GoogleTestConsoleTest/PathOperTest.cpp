#include <iostream>
#include "gtest/gtest.h"
#include "PathOper.h"

TEST(PathOperTest, GetFileName)
{
	std::string expect = "123.txt";
	std::string fullfileName = "D:\\ImgOut\\123.txt";

	std::string fileName = XYZCore::PathOper::GetFileName(fullfileName);

	EXPECT_EQ(expect, fileName);
}

TEST(PathOperTest, GetFileName_InputOnlyFileName)
{
	std::string expect = "123.txt";
	std::string fullfileName = "123.txt";

	std::string fileName = XYZCore::PathOper::GetFileName(fullfileName);

	EXPECT_EQ(expect, fileName);
}

TEST(PathOperTest, GetFileName_InputNoExtension)
{
	std::string expect = "123";
	std::string fullfileName = "D:\\ImgOut\\123";

	std::string fileName = XYZCore::PathOper::GetFileName(fullfileName);

	EXPECT_EQ(expect, fileName);
}


TEST(PathOperTest, GetFileName_without_extension)
{
	std::string expect = "123";
	std::string fullfileName = "D:\\ImgOut\\123.txt";

	std::string fileName = XYZCore::PathOper::GetFileNameWithoutExtension(fullfileName);

	EXPECT_EQ(expect, fileName);
}

TEST(PathOperTest, GetFileName_without_extension_InputOnlyFileName)
{
	std::string expect = "123";
	std::string fullfileName = "123.txt";

	std::string fileName = XYZCore::PathOper::GetFileNameWithoutExtension(fullfileName);

	EXPECT_EQ(expect, fileName);
}

TEST(PathOperTest, GetFileName_without_extension_InputNoExtension)
{
	std::string expect = "123";
	std::string fullfileName = "D:\\ImgOut\\123";

	std::string fileName = XYZCore::PathOper::GetFileNameWithoutExtension(fullfileName);

	EXPECT_EQ(expect, fileName);
}