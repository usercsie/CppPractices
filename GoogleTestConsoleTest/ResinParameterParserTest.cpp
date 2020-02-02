#include "gtest/gtest.h"
#include "ResinParameterParser.h"

using namespace XYZNobel;

TEST(ResinParameterParser, Read_FileNotFound_Return_1)
{
	std::string fullFileName = ".\\TestData\\Resin_notfound.csv";

	ResinParameterParser inst;
	int actual = inst.Read(fullFileName);

	EXPECT_EQ(1, actual);
}

TEST(ResinParameterParser, Read_Success)
{
	std::string fullFileName = ".\\TestData\\Resin.csv";
	ResinParameterParser inst;
	int actual = inst.Read(fullFileName);

	EXPECT_EQ(0, actual);
}