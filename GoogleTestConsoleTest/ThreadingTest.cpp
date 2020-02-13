#include "gtest/gtest.h"

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

namespace Threading_Async
{
	/*
	Async
	- The most convenient and straight-forward way to perform an asynchronous com­pu­ta­tion is via 
	the async function template, which returns the matching future immediately.
	*/

	int Compute(int iIn)
	{
		std::this_thread::sleep_for(std::chrono::seconds(iIn));
		return iIn;
	}

	TEST(ThreadingTest, Async_asyncOfpolicy)
	{
		auto tpStart = std::chrono::high_resolution_clock::now();

		std::future<int> fuRes1 = std::async(std::launch::async, Compute, 1);
		std::future<int> fuRes2 = std::async(std::launch::async, Compute, 2);

		std::this_thread::sleep_for(std::chrono::seconds(2));

		int iResult = fuRes1.get() + fuRes2.get();
		auto duTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - tpStart).count();
		
		EXPECT_EQ(3, iResult);
		EXPECT_EQ(2, duTime);
	}

	TEST(ThreadingTest, Async_deferredOfpolicy)
	{
		auto tpStart = std::chrono::high_resolution_clock::now();

		std::future<int> fuRes1 = std::async(std::launch::deferred, Compute, 1);
		std::future<int> fuRes2 = std::async(std::launch::deferred, Compute, 2);

		std::this_thread::sleep_for(std::chrono::seconds(2));

		int iResult = fuRes1.get() + fuRes2.get();
		auto duTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - tpStart).count();

		EXPECT_EQ(3, iResult);
		EXPECT_EQ(true, duTime > 2);
	}

	//TEST(ThreadingTest, Async_defaultOfpolicy)
	//{
	//	auto tpStart = std::chrono::high_resolution_clock::now();

	//	std::future<int> fuRes1 = std::async(Compute, 1);
	//	std::future<int> fuRes2 = std::async(Compute, 2);

	//	std::this_thread::sleep_for(std::chrono::seconds(2));

	//	int iResult = fuRes1.get() + fuRes2.get();
	//	auto duTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - tpStart).count();

	//	EXPECT_EQ(3, iResult);
	//	EXPECT_EQ(4, duTime);
	//}
}


namespace Threading_Promise
{
	/*
	Promise
	- The class template std::promise provides a facility to store a value or
	an exception that is later acquired asynchronously via a std::future object
	created by the std::promise object.
	*/

	void accumulate(std::vector<int>::iterator first,
		std::vector<int>::iterator last,
		std::promise<int> accumulate_promise)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		int sum = std::accumulate(first, last, 0);
		accumulate_promise.set_value(sum);  // Notify future
	}

	void accumulate_Thread_Exit(std::vector<int>::iterator first,
		std::vector<int>::iterator last,
		std::promise<int>& accumulate_promise)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		int sum = std::accumulate(first, last, 0);
		accumulate_promise.set_value_at_thread_exit(sum);
	}

	void do_work(std::promise<void> barrier)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		barrier.set_value();
	}

	//非同步thread, 回傳int結果
	TEST(ThreadingTest, Promise_set_value_Return_int)
	{
		// Demonstrate using promise<int> to transmit a result between threads.
		std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
		std::promise<int> accumulate_promise;
		std::future<int> accumulate_future = accumulate_promise.get_future();
		std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
			std::move(accumulate_promise));

		// future::get() will wait until the future has a valid result and retrieves it.
		// Calling wait() before get() is not needed
		//std::cout << "waiting..." << std::endl;
		//accumulate_future.wait();  // wait for result
		int actual = accumulate_future.get();
		//std::cout << "result=" << actual << '\n';
		work_thread.join();  // wait for thread completion
		EXPECT_EQ(21, actual);
	}

	//非同步thread, 回傳int結果
	TEST(ThreadingTest, Promise_set_value_exit_Return_int)
	{
		std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
		std::promise<int> accumulate_promise;
		std::future<int> accumulate_future = accumulate_promise.get_future();
		std::thread work_thread(accumulate_Thread_Exit, numbers.begin(), numbers.end(),
			std::ref(accumulate_promise));
		work_thread.detach();

		// future::get() will wait until the future has a valid result and retrieves it.
		// Calling wait() before get() is not needed
		//std::cout << "waiting..." << std::endl;
		accumulate_future.wait();  // wait for result

		int actual = accumulate_future.get();
		//std::cout << "result=" << actual << '\n';
		EXPECT_EQ(21, actual);
	}

	//TEST(ThreadingTest, Promise_Return_void_as_Signal)
	//{
	//	// Demonstrate using promise<void> to signal state between threads.
	//	std::promise<void> barrier;
	//	std::future<void> barrier_future = barrier.get_future();
	//	std::thread new_work_thread(do_work, std::move(barrier));
	//	barrier_future.wait();
	//	new_work_thread.join();
	//}
}

namespace Threading_Lock
{	
	TEST(ThreadingTest, Lock_wait)
	{
		std::mutex mutex;
		std::condition_variable cv;
		std::unique_lock<std::mutex> lk(mutex);
		
		int i = 0;
		std::thread([&]
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));	
			i = 1;
			cv.notify_one();
		}).detach();

		//bool flag = cv.wait_for(lk, std::chrono::seconds(5), [&]() {return i == 1; });
		cv.wait(lk);
		EXPECT_EQ(1, i);
	}

	TEST(ThreadingTest, Lock_wait_for)
	{
		std::mutex mutex;
		std::condition_variable cv;
		std::unique_lock<std::mutex> lk(mutex);

		int i = 0;
		std::thread([&]
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			i = 1;
			cv.notify_one();
		}).detach();
		
		bool flag = cv.wait_for(lk, std::chrono::seconds(10), [&]() {return i == 1; });
		EXPECT_EQ(true, flag);
		EXPECT_EQ(1, i);
	}
}