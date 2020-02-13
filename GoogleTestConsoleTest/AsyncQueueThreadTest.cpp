#include "gtest\gtest.h"
#include "AsyncQueueThread.h"

TEST(AsyncQueueThread, DefaultQueue)
{
	XYZCore::AsyncQueueThread<int> cw(10);

	int n = 1;
	cw.Add([&](int id)
	{
		n = id;
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(10, n);
}

TEST(AsyncQueueThread, SpecifiedQueue)
{
	std::shared_ptr<XYZCore::ConcurrentQueue<XYZCore::Action>> q = std::make_shared<XYZCore::ConcurrentQueue<XYZCore::Action>>();

	XYZCore::AsyncQueueThread<int> cw(q, 10);

	int n = 1;
	cw.Add([&](int id)
	{
		n = id;
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(10, n);	
}