#include "UniquePtrTest.h"
#include <cassert>
#include <functional>

class baseClass
{
public:
	virtual void Action() = 0;
};

class derivedClass1 : public baseClass
{
public:
	void Action() override
	{

	}
};

class derivedClass2 : public baseClass
{
public:
	void Action() override
	{

	}
};

class baseWrapper
{
public:
	void Action(baseClass *base)
	{
		base->Action();
	}
};

class Factory
{
public:
	static std::unique_ptr<baseClass> Create(int type)
	{
		if (type == 0)	return std::make_unique<derivedClass1>();
		else if (type == 1)return std::make_unique<derivedClass2>();
		else assert(false, "undefined type");
	}
};

TEST(UniquePtrTest, FactoryPattern)
{
	std::unique_ptr<baseClass> base = Factory::Create(0);
	base->Action();
}

TEST(UniquePtrTest, Get)
{
	std::unique_ptr<baseClass> base = Factory::Create(0);

	baseWrapper wrapper;
	wrapper.Action(base.get());
}


int add(int a, int b) { return (a + b); }
int sub(int a, int b) { return (a - b); }
int mul(int a, int b) { return (a * b); }
double divide(double a, double b) { return (a / b); }

int compute(int a, int b, std::function<int(int,int)> op) 
{ 
	return op(a, b);
}

int compute2(int a, int b, int(*funcPtr)(int, int))
{
	return funcPtr(a, b);
}

class ComputeClass
{
public:
	int Add(int a, int b)
	{
		int extra = 10;
		return compute(a, b, [=](int a, int b)
		{
			return a + b + extra;
		});
	}
	int Add2(int a, int b)
	{
		int extra = 10;
		return compute(a, b, [=](int a, int b)
		{
			return a + b + extra;
		});
	}
};

TEST(Functor, functionPointer)
{
	int(*AddNumber1)(int, int) = add;
	EXPECT_EQ(3, AddNumber1(1, 2));

	int n = 10;
	int(*AddNumber2)(int, int)
					{		
						[](int a, int b) {return a + b; }
					};
	EXPECT_EQ(3, AddNumber2(1, 2));

	std::function AddNumber3
	{
		[](int a, int b) {return a + b; }
	};
	EXPECT_EQ(3, AddNumber3(1, 2));
}

TEST(Functor, lambda)
{
	int actual = compute(1, 2, [](int a, int b) -> int
								{
									return a + b;
								});
	EXPECT_EQ(3, actual);
}

