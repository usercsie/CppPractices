#include <iostream>
#include "gtest/gtest.h"

struct IEventHander
{
	virtual void Callback(int num) = 0;
};

struct Publisher
{
	std::vector<std::shared_ptr<IEventHander>> _Callbacks;
public:

	void Connect(std::shared_ptr<IEventHander> callback)
	{
		_Callbacks.push_back(callback);
	}

	~Publisher()
	{
		std::cout << "Publisher was disposed." << std::endl;
	}

	void DoSomething()
	{
		Notify();
	}

	void Notify()
	{
		for (auto c : _Callbacks)
		{
			if (c != nullptr)
			{
				c->Callback(1);
			}
		}
	}
};


struct Observer : IEventHander
{	
	std::shared_ptr<Publisher> _Publisher;
public:
	int Number;

	~Observer()
	{
		std::cout << "Observer was disposed." << std::endl;
	}

	Observer(std::shared_ptr<Publisher> ptr)
	{
		_Publisher = ptr;
	}

	void DoSomething()
	{
		_Publisher->DoSomething();
	}

	void Callback(int num) override
	{
		Number = num;
	};
};

TEST(ObserverPatternTest, Callback)
{
	std::shared_ptr<Publisher> pb = std::make_shared<Publisher>();
	std::shared_ptr<Observer> os = std::make_shared<Observer>(pb);
	std::shared_ptr<IEventHander> eh = std::static_pointer_cast<IEventHander>(os);

	/*EXPECT_EQ(2, os.use_count());
	EXPECT_EQ(2, eh.use_count());*/

	pb->Connect(eh);

	/*EXPECT_EQ(3, os.use_count());
	EXPECT_EQ(3, eh.use_count());*/

	os->DoSomething();	

	EXPECT_EQ(1, os->Number);
}