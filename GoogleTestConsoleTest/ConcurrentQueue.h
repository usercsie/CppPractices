//
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace XYZCore
{
	template <typename T>
	class ConcurrentQueue
	{
	public:

		T pop()
		{
			std::unique_lock<std::mutex> mlock(mutex_);
			while (queue_.empty())
			{
				cond_.wait(mlock);
			}
			auto val = queue_.front();
			queue_.pop();
			return val;
		}

		void pop(T& item)
		{
			std::unique_lock<std::mutex> mlock(mutex_);
			while (queue_.empty())
			{
				cond_.wait(mlock);
			}
			item = queue_.front();
			queue_.pop();
		}

		void push(const T& item)
		{
			std::unique_lock<std::mutex> mlock(mutex_);
			queue_.push(item);
			mlock.unlock();
			cond_.notify_one();
		}

		int count()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return queue_.size();
		}

		ConcurrentQueue() = default;
		ConcurrentQueue(const ConcurrentQueue&) = delete;            // disable copying
		ConcurrentQueue& operator=(const ConcurrentQueue&) = delete; // disable assignment

	private:
		std::queue<T> queue_;
		std::mutex mutex_;
		std::condition_variable cond_;
	};
}