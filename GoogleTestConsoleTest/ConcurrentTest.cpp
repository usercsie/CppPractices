#include "gtest\gtest.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
#include "Concurrent.h"

using namespace XYZCore;

TEST(ConcurrentTest, Test)
{
	Concurrent<std::vector<int>> cv{ std::vector<int>{1,2,3,4,5,6,7,8,9,10} };
	auto f1 = cv([](std::vector<int>& v) 
	{		
		return std::accumulate(v.begin(), v.end(), 0);
	});
	auto f2 = cv([](std::vector<int>& v)->bool 
	{
		std::iota(v.begin(), v.end(), 0);		
		return true;
	});
	auto f3 = cv([](std::vector<int>& v) 
	{
		return std::accumulate(v.begin(), v.end(), 0);
	});
	
	auto f4 = cv([](std::vector<int>& v) 
	{
		return v.size();
	});
	
	auto f5 = cv([](std::vector<int>&) {});

	EXPECT_EQ(55, f1.get());
	EXPECT_EQ(true, f2.get());
	EXPECT_EQ(45, f3.get());
	EXPECT_EQ(10, f4.get());	
}