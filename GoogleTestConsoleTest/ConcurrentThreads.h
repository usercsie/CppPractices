#pragma once

#include <vector>
#include <chrono>
#include "ConcurrentQueue.h"
#include "AsyncQueueThread.h"

namespace XYZCore
{
	template<typename T>
	class ConcurrentThreads
	{		
	public:
		ConcurrentThreads(int threadNum, T resource = T{})
			:
			resource_{ resource }
		{
			queue_ = std::make_shared < ConcurrentQueue<Action>>();			

			for (int n = 0; n < threadNum; n++)
			{
				worker_.push_back(new AsyncQueueThread<T>(queue_, resource_));
			}
		}

		~ConcurrentThreads()
		{
			for (int n = 0; n < worker_.size(); n++)
			{				
				delete worker_[n];
			}
			worker_.clear();
		}

		template <typename F>
		void AddTask(F f, int token) const
		{
			queue_->push([=]
			{
				f(resource_);
				token_.push(token);				
			});
		}

		template <typename F>
		void AddTask(F f) const
		{
			queue_->push([=]
			{
				f(resource_);
			});
		}

		int GetToken(int timeOut = 5000)
		{
			std::unique_lock<std::mutex> lk(cv_mutex_);

			while (token_.count() == 0)
			{
				if (_cv.wait_for(lk, std::chrono::milliseconds(timeOut), [this] {return token_.count() > 0; }) == false)
					return -1;
			}

			return token_.pop();
		}

	private:
		mutable std::shared_ptr<ConcurrentQueue<Action>> queue_;
		mutable ConcurrentQueue<int> token_;
		mutable T resource_;
		std::vector<AsyncQueueThread<T>*> worker_;						

		std::mutex cv_mutex_;
		std::condition_variable _cv;
	};
}
