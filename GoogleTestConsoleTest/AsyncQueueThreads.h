#pragma once

#include <functional>
#include <thread>
#include "ConcurrentQueue.h"

namespace XYZCore
{
	typedef std::function<void()> Action;
	template <typename T>
	class AsyncQueueThreads
	{
	public:

		AsyncQueueThreads(int threadNum = 1, T resource = T{})
			:
			resource_{ resource },
			done_{ false }
		{
			for (int n = 0; n < threadNum; n++)
			{
				worker_.push_back
				(
					std::thread([this]()
					{
						while (!done_)
						{
							queue_.pop()();
							std::cout << "pop." << std::this_thread::get_id() << "===>" << done_ << std::endl;
						}
					})
				);
			}
		}

		~AsyncQueueThreads()
		{			
			for (int n = 0; n < worker_.size(); n++)
			{
				queue_.push([this] {done_ = true; });
			}
			
			for (auto& w : worker_)
			{
				w.join();
				std::cout << "Thread terminated." << std::endl;
			}			
		}

		template <typename F>
		void Add(F f) const
		{
			queue_.push([=]
			{
				f(resource_);
			});
		}		

		template <typename F>
		void Add(F f, int token) const
		{
			queue_.push([=]
			{
				f(resource_);
				token_.push(token);
			});
		}

		//Return -1 means time out, otherwise return token.
		int GetToken(int timeOut = 5000)
		{
			std::unique_lock<std::mutex> lk(cv_mutex_);

			while (token_.count() == 0)
			{
				if (cv_.wait_for(lk, std::chrono::milliseconds(timeOut), [this] {return token_.count() > 0; }) == false)
					return -1;
			}

			return token_.pop();
		}

		bool Wait(int timeOut = 5000)
		{
			std::unique_lock<std::mutex> lk(cv_mutex_);

			while (queue_.count() > 0)
			{
				if (cv_.wait_for(lk, std::chrono::milliseconds(timeOut), [this] {return queue_.count() == 0; }) == false)
					return false;
			}

			return true;
		}

	private:

		mutable ConcurrentQueue<Action> queue_;
		mutable ConcurrentQueue<int> token_;
		mutable T resource_;
		std::vector<std::thread> worker_;
		bool done_;

		std::mutex cv_mutex_;
		std::condition_variable cv_;
	};
}
