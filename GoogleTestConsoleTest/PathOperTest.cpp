#include <iostream>
#include "gtest/gtest.h"
#include "PathOper.h"

//TEST(PathOperTest, GetFileName_with_extension)
//{
//	std::string expect = "123.txt";
//	std::string fullfileName = "D:\\ImgOut\\123.txt";
//
//	std::string fileName = XYZCore::PathOper::GetFileName(fullfileName);
//
//	EXPECT_EQ(expect, fileName);
//}
//
//TEST(PathOperTest, GetFileName_without_extension)
//{
//	std::string expect = "123";
//	std::string fullfileName = "D:\\ImgOut\\123.txt";
//
//	std::string fileName = XYZCore::PathOper::GetFileName(fullfileName, false);
//
//	EXPECT_EQ(expect, fileName);
//}