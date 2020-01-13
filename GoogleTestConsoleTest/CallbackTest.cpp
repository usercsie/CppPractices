#include <iostream>
#include "gtest/gtest.h"

class Signal {

	// store all callbacks to a string map
	std::map<std::string, std::function<void()>> callbacks;

	// check if callback already exists. optional
	bool exists(std::string key) {
		if (callbacks.find(key) == callbacks.end()) { return false; }
		else { return true; }
	}

public:
	void add(std::string key, std::function<void()> cb) {
		if (!exists(key)) { remove(key); }
		callbacks.insert(std::pair<std::string, std::function<void()>>(key, cb));
	}
	void remove(std::string key) {
		callbacks.erase(key);
	}
	void dispatch() {
		for (std::map<std::string, std::function<void()>>::iterator it = callbacks.begin(); it != callbacks.end(); it++) {
			callbacks[it->first]();
		}
	}

	// this destroys the signal
	void dispose() {
		callbacks.clear();
	}
};

class EventArgs
{
public:
	~EventArgs()
	{
		std::cout << "EventArgs was disposed." << std::endl;
	}
	int Param1;
	int Param2;
};

class PublisherLamda
{
public:
	~PublisherLamda()
	{
		std::cout << "PublisherLamda was disposed." << std::endl;
	}

	std::function<void(std::shared_ptr<EventArgs>)> Callback;

	void Action()
	{		
		OnActionCallback();
	};

private:
	void OnActionCallback()
	{
		if (Callback != nullptr)
		{
			std::shared_ptr<EventArgs> ptr = std::make_shared<EventArgs>();
			ptr->Param1 = 1;
			ptr->Param2 = 2;
			Callback(ptr);
		}
	}
};

class ObserverLamda
{
public:
	bool GotCallBack = false;
	int GotValue;
	int GotValueFromHandler;
	std::shared_ptr<EventArgs> Args;	
	std::shared_ptr<PublisherLamda> _Inst;

	~ObserverLamda()
	{
		std::cout << "ObserverLamda was disposed." << std::endl;
	}

	ObserverLamda(std::shared_ptr<PublisherLamda> publisher)
	{
		_Inst = publisher;
		_Inst->Callback = [&](std::shared_ptr<EventArgs> args)
		{						
			Args = args;			
		};					
	}

	void Action()
	{
		_Inst->Action();
	}	
};

TEST(CallbackFuncTest, Callback_Raised)
{
	std::shared_ptr<PublisherLamda> publisher = std::make_shared<PublisherLamda>();
	std::unique_ptr<ObserverLamda> inst = std::make_unique<ObserverLamda>(publisher);	
	
	inst->Action();
	
	EXPECT_EQ(1, inst->Args->Param1);
	EXPECT_EQ(2, inst->Args->Param2);	
}