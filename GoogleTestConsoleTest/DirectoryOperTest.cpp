#include "gtest/gtest.h"
#include "DirectoryOper.h"

TEST(DirectoryOperTest, Exists)
{
	std::string path = ".\\TestData\\TestFolder";
	bool actual = XYZCore::DirectoryOper::Exists(path);	

	EXPECT_EQ(false, actual);
}

TEST(DirectoryOperTest, Exists2)
{
	std::string path = ".\\TestData\\TestFolder\\";
	bool actual = XYZCore::DirectoryOper::Exists(path);

	EXPECT_EQ(false, actual);
}

TEST(DirectoryOperTest, Exists_uniCode)
{
	std::wstring path = L".\\TestData\\測試Folder";
	bool actual = XYZCore::DirectoryOper::Exists(path);

	EXPECT_EQ(false, actual);
}

TEST(DirectoryOperTest, Exists2_uniCode)
{
	std::wstring path = L".\\TestData\\測試Folder\\";
	bool actual = XYZCore::DirectoryOper::Exists(path);

	EXPECT_EQ(false, actual);
}

TEST(DirectoryOperTest, Create)
{
	std::string path = ".\\TestData\\CreateFolder";
	bool actual = XYZCore::DirectoryOper::Create(path);

	EXPECT_EQ(true, actual);
	EXPECT_EQ(true, XYZCore::DirectoryOper::Exists(path));

	//if folder already existed, return true.
	actual = XYZCore::DirectoryOper::Create(path);
	EXPECT_EQ(true, actual);

	EXPECT_EQ(true, XYZCore::DirectoryOper::Delete(path));
}

TEST(DirectoryOperTest, Create_uniCode)
{
	std::wstring path = L".\\TestData\\建立Folder";
	bool actual = XYZCore::DirectoryOper::Create(path);

	EXPECT_EQ(true, actual);
	EXPECT_EQ(true, XYZCore::DirectoryOper::Exists(path));

	//if folder already existed, return true.
	actual = XYZCore::DirectoryOper::Create(path);
	EXPECT_EQ(true, actual);

	EXPECT_EQ(true, XYZCore::DirectoryOper::Delete(path));
}
