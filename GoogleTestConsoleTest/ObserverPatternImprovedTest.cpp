#include <iostream>
#include <vector>
#include "gtest/gtest.h"

template <class T>
class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void update(T *subject) = 0;
};

template <class T>
class Subject
{
public:
	Subject() {}
	virtual ~Subject() {}
	void attach(Observer<T> &observer)
	{
		_Observers.push_back(&observer);
	}

	void notify()
	{		
		for (auto it : _Observers)
		{
			if (it != nullptr)
			{
				it-> update(static_cast<T *>(this));
			}
		}
	}
private:
	std::vector<Observer<T> *> _Observers;
};

class TransferStartHandler : public Subject<TransferStartHandler>
{
public:
	~TransferStartHandler() { std::cout << "TransferStartHandler was disposed." << std::endl; }	
	void TransferStarting() { notify(); }
};

class TransferEndHandler : public Subject<TransferEndHandler>
{
public:
	~TransferEndHandler() { std::cout << "TransferEndHandler was disposed." << std::endl; }
	void TransferFinished() { notify(); }
};

class TransferProgressHandler : public Subject<TransferProgressHandler>
{
public:
	~TransferProgressHandler() { std::cout << "TransferProgressHandler was disposed." << std::endl; }
	void TransferProgressChanged(int value) 
	{
		_Progress = value;
		notify(); 
	}

	int GetProgress()
	{
		return _Progress;
	}
private:	
	int _Progress;
};

class TransferWindow : public Observer<TransferStartHandler>, public Observer<TransferEndHandler>, 
	public Observer<TransferProgressHandler>
{	
public:
	bool StartFlag, EndFlag;
	int Progress;
	void update(TransferStartHandler *subject)
	{
		StartFlag = true;
		std::cout << "file transfer start." << std::endl;
	}

	void update(TransferEndHandler *subject)
	{
		EndFlag = true;
		std::cout << "file transfer finished." << std::endl;
	}

	void update(TransferProgressHandler *subject)
	{
		Progress = subject->GetProgress();
		std::cout << "file transfer progress: " << subject->GetProgress() << " %" << std::endl;
	}
};

TEST(ObserverPatternImprovedTest, FileTransfer)
{
	TransferWindow win;
	TransferStartHandler transferStart;
	TransferEndHandler transferEnd;
	TransferProgressHandler transferProgress;

	transferStart.attach(win);
	transferEnd.attach(win);
	transferProgress.attach(win);

	for (int n = 0; n < 100; n++)
	{
		if (n == 0)
		{
			transferStart.TransferStarting();
		}
		else
		{
			transferProgress.TransferProgressChanged(n);
		}

		if (n == 99)
		{
			transferEnd.TransferFinished();
		}
	}

	EXPECT_EQ(true, win.StartFlag);
	EXPECT_EQ(true, win.EndFlag);
	EXPECT_EQ(99, win.Progress);
}