#include <iostream>
#include "gtest/gtest.h"
#include "ConcurrentWrapper.h"
#include <thread>
#include <future>

TEST(ConcurrentWrapper, AsyncExecution)
{
	XYZCore::ConcurrentWrapper<int> cw(10);

	int n = 1;
	cw([&](int id)
	{
		n = id;		
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(10, n);
}