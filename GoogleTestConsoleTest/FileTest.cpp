#include <iostream>
#include "gtest/gtest.h"
#include <fstream>
#include <ios>

TEST(FileTest, ReadWriteBinaryFile)
{
	std::string fileName = "FileTest_WriteFile.data";

	std::fstream writer;
	writer.open(fileName, std::ios_base::out | std::ios_base::binary);

	int num = 428;
	std::string str = std::to_string(num);
	const char *ptr = str.c_str();
	writer.write(ptr, str.length());
	writer.close();

	//---Reader

	std::vector<char> buffer(str.length());

	std::fstream reader;
	reader.open(fileName, std::ios_base::in | std::ios_base::binary);
	reader.read(&buffer[0], str.length());
	reader.close();

	int actual;
	std::memcpy(&actual, &buffer[0], buffer.size());

	EXPECT_EQ(num, actual);
}