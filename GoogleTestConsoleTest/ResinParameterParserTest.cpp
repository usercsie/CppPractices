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

TEST(ResinParameterParser, Read_Success_JudgeLevelTable)
{
	std::string fullFileName = ".\\TestData\\Resin.csv";
	ResinParameterParser inst;
	int error = inst.Read(fullFileName);

	ASSERT_EQ(0, error);

	std::vector<int> table = inst.GetMaxWidth("M1", "L_BLACK", "0.1", "QUALITY_STANDARD");
	EXPECT_EQ(5, table[0]);
	EXPECT_EQ(8, table[1]);
	EXPECT_EQ(10, table[2]);
	EXPECT_EQ(0, table[3]);

	table = inst.GetAngle("M1", "L_BLACK", "0.1", "QUALITY_STANDARD");
	EXPECT_EQ(90, table[0]);
	EXPECT_EQ(200, table[1]);
	EXPECT_EQ(350, table[2]);
	EXPECT_EQ(0, table[3]);

	table = inst.GetTotalArea("M1", "L_BLACK", "0.1", "QUALITY_STANDARD");
	EXPECT_EQ(180, table[0]);
	EXPECT_EQ(400, table[1]);
	EXPECT_EQ(700, table[2]);
	EXPECT_EQ(0, table[3]);

	table = inst.GetMaxDistance("M1", "L_BLACK", "0.1", "QUALITY_STANDARD");
	EXPECT_EQ(0, table[0]);
	EXPECT_EQ(0, table[1]);
	EXPECT_EQ(0, table[2]);
	EXPECT_EQ(0, table[3]);

	//test key not found return empty table.
	table = inst.GetMaxDistance("M10", "L_BLACK", "0.1", "QUALITY_STANDARD");
	EXPECT_EQ(0, table.size());
}

TEST(ResinParameterParser, Read_Success_PowerTable)
{
	std::string fullFileName = ".\\TestData\\Resin.csv";
	ResinParameterParser inst;
	int error = inst.Read(fullFileName);

	ASSERT_EQ(0, error);

	std::string p = inst.GetPowerTable("M1", "L_BLACK", "0.1", "QUALITY_STANDARD", "0");
	EXPECT_EQ("0,37,4,26,3000,1,10,0,6,10,0,6,0,3000,95,0,1300,4,5,0,6,10,0,6,0,2000,75,300,0,7,7,7,7", p);

	p = inst.GetPowerTable("M1", "L_BLACK", "0.05", "QUALITY_STANDARD", "0");
	EXPECT_EQ("0,37,4,56,3000,1,10,0,6,10,0,6,0,2000,95,0,1000,1,5,0,6,15,0,6,0,2000,70,200,0,7,7,6,6", p);

	p = inst.GetPowerTable("M2", "L_BLACK_M2", "0.1", "QUALITY_STANDARD", "0");
	EXPECT_EQ("1,38,2,5,1500,2,15,0,4,10,0,2,0,5000,70,0,500,2,1,0,6,0,0,6,0,300,100,0,0,7,7,6,6", p);
}