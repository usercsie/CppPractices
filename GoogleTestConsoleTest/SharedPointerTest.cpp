#include <iostream>
#include "gtest/gtest.h"

TEST(SharedPointerTest, MakePointer)
{
	std::shared_ptr<int> p1 = std::make_shared<int>(100);
	std::shared_ptr<int> p2(new int(1000));
	int* temp = new int(10000);
	std::shared_ptr<int> p3(temp);		

	EXPECT_EQ(100, *p1);	
	EXPECT_EQ(1000, *p2);
	EXPECT_EQ(10000, *p3);		
}

TEST(SharedPointerTest, UseCount)
{
	std::shared_ptr<int> p1 = std::make_shared<int>(100);
	
	EXPECT_EQ(1, p1.use_count());

	std::shared_ptr<int> p2 = p1;

	EXPECT_EQ(2, p2.use_count());
	EXPECT_EQ(2, p1.use_count());

	p1.reset();

	EXPECT_EQ(0, p1.use_count());
	EXPECT_EQ(1, p2.use_count());
}

void func(std::shared_ptr<int> sp)
{
	*sp = 101;

	EXPECT_EQ(2, sp.use_count());
};

TEST(SharedPointerTest, func_args)
{
	std::shared_ptr<int> p1 = std::make_shared<int>(100);

	func(p1);

	EXPECT_EQ(101, *p1);
	EXPECT_EQ(1, p1.use_count());
}

class DataGenerator
{
public:
	DataGenerator()
	{
		_Pointer = std::make_shared<int>(0);
	}

	std::shared_ptr<int> GetPointer()
	{
		return _Pointer;
	};
private:
	std::shared_ptr<int> _Pointer;
};

TEST(SharedPointerTest, GetPointer)
{
	DataGenerator inst;

	std::shared_ptr<int> p = inst.GetPointer();

	EXPECT_EQ(2, p.use_count());	
}

struct baseClass{};
struct deriveClass : baseClass{};
TEST(SharedPointerTest, CaseDerivedToBaseClass)
{
	std::shared_ptr<deriveClass> derive = std::make_shared<deriveClass>();
	std::shared_ptr<baseClass> base = std::static_pointer_cast<baseClass>(derive);

	EXPECT_EQ(2, base.use_count());	
}
