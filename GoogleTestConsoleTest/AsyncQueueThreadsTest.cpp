#include "gtest\gtest.h"
#include "AsyncQueueThreads.h"

TEST(AsyncQueueThreads, SingleThread)
{
	int threadNum = 1;
	int res = 10;
	XYZCore::AsyncQueueThreads<int> cw(threadNum, res);

	int n = 0;
	cw.Add([&](int res)
	{
		n = res;
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(res, n);
}

TEST(AsyncQueueThreads, TwoThreads)
{
	int threadNum = 2;
	int res = 10;
	XYZCore::AsyncQueueThreads<int> cw(threadNum, res);

	std::mutex mtx;
	int n = 0;
	for (int m = 0; m < threadNum; m++)
	{
		cw.Add([&](int& res)
		{
			std::lock_guard<std::mutex> guard(mtx);
			n += res;
		});
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(threadNum * res, n);
}

void DoSomething2(int second)
{
	std::this_thread::sleep_for(std::chrono::seconds(second));
}

TEST(AsyncQueueThreads, GetToken_TimeOut)
{
	int threadNum = 1;
	XYZCore::AsyncQueueThreads<std::string> th(threadNum, "");

	int token = 1;
	th.Add([](std::string s)
	{
		DoSomething2(2);
	}, token);

	int actual = th.GetToken(1000);//sec

	EXPECT_EQ(-1, actual);
}

TEST(AsyncQueueThreads, GetToken_Success)
{
	int threadNum = 1;
	XYZCore::AsyncQueueThreads<std::string> th(threadNum, "");

	int token = 1;
	th.Add([](std::string s)
	{
		DoSomething2(2);
	}, token);

	int actual = th.GetToken();

	EXPECT_EQ(token, actual);
}

TEST(AsyncQueueThreads, GetToken_Success_4Threads)
{
	int threadNum = 4;
	XYZCore::AsyncQueueThreads<std::string> th(threadNum, "");

	th.Add([](std::string s) {DoSomething2(4); }, 0);
	th.Add([](std::string s) {DoSomething2(3); }, 1);
	th.Add([](std::string s) {DoSomething2(2); }, 2);
	th.Add([](std::string s) {DoSomething2(1); }, 3);

	EXPECT_EQ(3, th.GetToken());
	EXPECT_EQ(2, th.GetToken());
	EXPECT_EQ(1, th.GetToken());
	EXPECT_EQ(0, th.GetToken());
}

TEST(AsyncQueueThreads, Wait_Success_4Threads)
{
	int threadNum = 4;
	XYZCore::AsyncQueueThreads<std::string> th(threadNum, "");

	auto tpStart = std::chrono::high_resolution_clock::now();

	th.Add([](std::string s) {DoSomething2(4); }, 0);
	th.Add([](std::string s) {DoSomething2(3); }, 1);
	th.Add([](std::string s) {DoSomething2(2); }, 2);
	th.Add([](std::string s) {DoSomething2(1); }, 3);	

	bool flag = th.Wait(10000);//wait all tasks finished.

	auto duTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - tpStart).count();	

	EXPECT_EQ(true, duTime > 3.9);
	EXPECT_EQ(3, th.GetToken());
	EXPECT_EQ(2, th.GetToken());
	EXPECT_EQ(1, th.GetToken());
	EXPECT_EQ(0, th.GetToken());
}