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

typedef void* Address;
typedef std::function<void(Address)> EnevtHandler;

class Publisher
{
public:
	~Publisher()
	{
		std::cout << "Publisher was disposed." << std::endl;
	}	

	void Action()
	{
		OnActionCallback();
	};

	void Register(Address adr, EnevtHandler e)
	{
		_ObserverPtr = adr;
		Callback = e;
	}
private:
	EnevtHandler Callback;
	Address _ObserverPtr;
	void OnActionCallback()
	{
		if (Callback != nullptr)
		{				
			Callback(_ObserverPtr);
		}
	}
};

class ObserverStatic
{
public:
	bool GotCallBack = false;

	~ObserverStatic()
	{
		std::cout << "ObserverStatic was disposed." << std::endl;
	}

	static void Callback(Address ptr)
	{
		reference_to<ObserverStatic>(ptr).OnCallback();
	}
private:

	void OnCallback()
	{
		GotCallBack = true;
	}

	template<class W>
	static W& reference_to(Address pw)
	{
		return *static_cast<W*>(pw);
	}
};

TEST(CallbackFuncTest, StaticCallback)
{	
	ObserverStatic * ob = new ObserverStatic();
	std::shared_ptr<Publisher> spb = std::make_shared< Publisher>();
	std::shared_ptr<ObserverStatic> sob(ob);
	spb->Register(ob, ObserverStatic::Callback);

	spb->Action();

	EXPECT_EQ(true, sob->GotCallBack);
}

class ObserverLamda
{
public:
	bool GotCallBack = false;

	ObserverLamda(std::shared_ptr< Publisher> publisher)
	{
		publisher->Register(this, [&](Address)
		{
			GotCallBack = true;
		});
	}

	~ObserverLamda()
	{
		std::cout << "ObserverLamda was disposed." << std::endl;
	}
};

TEST(CallbackFuncTest, LamdaCallback)
{
	std::shared_ptr<Publisher> spb = std::make_shared< Publisher>();
	ObserverLamda * ob = new ObserverLamda(spb);
	std::shared_ptr<ObserverLamda> sob(ob);	

	spb->Action();

	EXPECT_EQ(true, sob->GotCallBack);
}