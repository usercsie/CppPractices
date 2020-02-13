#pragma once

#include <functional>
#include <thread>
#include "ConcurrentQueue.h"

namespace XYZCore
{
	typedef std::function<void()> Action;
	template <typename T>
	class AsyncQueueThread
	{
	public:

		AsyncQueueThread(T resource = T{})
			:
			resource_{ resource },
			done_{ false }
		{
			queue_ = std::make_shared<ConcurrentQueue<Action>>();
			StartWorker();
		}
		AsyncQueueThread(std::shared_ptr<ConcurrentQueue<Action>> queue, T resource = T{})
			:
			resource_{ resource },
			done_{ false }
		{			
			queue_ = queue;
			StartWorker();
		}

		~AsyncQueueThread()
		{
			//std::cout << "Thread terminating: " << std::this_thread::get_id() << std::endl;

			queue_->push([this] {done_ = true; });
			queue_->push([this] {done_ = true; });			
			queue_->push([this] {done_ = true; });			
			queue_->push([this] {done_ = true; });
			worker_.join();

			std::cout << "Thread terminated." << std::this_thread::get_id() << std::endl;
		}

		template <typename F>
		void Add(F f) const
		{
			queue_->push([=]
			{
				f(resource_);
			});
		}

	private:

		mutable std::shared_ptr<ConcurrentQueue<Action>> queue_;		
		mutable T resource_;
		std::thread worker_;
		bool done_;		

		void StartWorker()
		{
			worker_ = std::thread([this]
			{
				while (!done_)
				{					
					queue_->pop()();		
					std::cout << "pop." << std::this_thread::get_id() << "===>" << done_ << std::endl;
				}
			});
		}
	};
}
