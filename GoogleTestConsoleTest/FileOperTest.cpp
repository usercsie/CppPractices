#include "gtest/gtest.h"
#include "FileOper.h"

TEST(FileOperTest, CreateFile)
{
	std::string fileName = ".\\TestData\\NewFile.txt";
	bool actual = XYZCore::FileOper::CreateFile(fileName);
	
	EXPECT_EQ(true, actual);
	EXPECT_EQ(true, XYZCore::FileOper::FileExisted(fileName));

	XYZCore::FileOper::DeleteFile(fileName);
}

TEST(FileOperTest, FileExistNotFound)
{
	bool actual = XYZCore::FileOper::FileExisted("D:\\ab.txt");

	EXPECT_EQ(false, actual);
}

TEST(FileOperTest, Write_Read_string)
{
	std::string fileName = ".\\TestData\\Write_Read_String.txt";
	std::string content = "abcdef";

	XYZCore::FileOper::WriteAllText(fileName, content);

	std::string actual = XYZCore::FileOper::ReadAllText(fileName);

	EXPECT_EQ(content, actual);
	XYZCore::FileOper::DeleteFile(fileName);
}

TEST(FileOperTest, Write_Read_Bytes)
{
	std::string fileName = ".\\TestData\\Write_Read_AllBytes.txt";
	std::string content = "abcdef";

	XYZCore::FileOper::WriteAllBytes(fileName, content.c_str(), content.length());

	std::vector<unsigned char> buffer = XYZCore::FileOper::ReadAllBytes(fileName);
	std::string actual(buffer.begin(), buffer.end());

	EXPECT_EQ(content, actual);
	XYZCore::FileOper::DeleteFile(fileName);
}

TEST(FileOperTest, Write_Read_Lines)
{
	std::string fileName = ".\\TestData\\Write_Read_Lines.txt";

	std::vector<std::string> lines
	{
		"ABC",
		"def",
		"GHI"
	};

	XYZCore::FileOper::WriteAllLines(fileName, lines);

	std::vector<std::string> actual = XYZCore::FileOper::ReadAllLines(fileName);

	EXPECT_EQ(lines, actual);
	XYZCore::FileOper::DeleteFile(fileName);
}