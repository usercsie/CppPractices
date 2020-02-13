#include "gtest\gtest.h"
#include "ConcurrentThreads.h"
#include "ConcurrentQueue.h"

using namespace XYZCore;

void DoSomething(int second)
{	
	std::this_thread::sleep_for(std::chrono::seconds(second));
}

TEST(ConcurrentThreads, GetToken_Timeout_Return_minus1)
{
	ConcurrentThreads<std::string> th(1, "");

	int token = 1;
	th.AddTask([&](std::string s)
	{
		DoSomething(2);
	}, token);

	int actual = th.GetToken(1000);//1sec

	EXPECT_EQ(-1, actual);
}

TEST(ConcurrentThreads, GetToken_Success)
{	
	ConcurrentThreads<std::string> th(1, "");

	int token = 1;
	th.AddTask([&](std::string s)
	{
		DoSomething(2);
	}, token);

	int actual = th.GetToken();

	EXPECT_EQ(token, actual);
}

TEST(ConcurrentThreads, GetToken_Success_4Threads)
{
	ConcurrentThreads<std::string> th(4, "");

	th.AddTask([&](std::string s) {DoSomething(4); }, 0);
	th.AddTask([&](std::string s) {DoSomething(3); }, 1);
	th.AddTask([&](std::string s) {DoSomething(2); }, 2);
	th.AddTask([&](std::string s) {DoSomething(1); }, 3);

	//EXPECT_EQ(3, th.GetToken());
	//EXPECT_EQ(2, th.GetToken());
	//EXPECT_EQ(1, th.GetToken());
	//EXPECT_EQ(0, th.GetToken());

	//system("pause");
}