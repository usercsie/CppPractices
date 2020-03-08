#include "TypeCastingTest.h"


TEST(TypeCastingTest, CStyle)
{
	double d = 2.4;
	int n = (int)d;

	EXPECT_EQ(2, n);
}

TEST(TypeCastingTest, StaticCast)
{
	double d = 2.4;
	int n = static_cast<int>(d);

	EXPECT_EQ(2, n);
}


class dynamicBase
{
public:
	virtual int Get() = 0;
};

class dynamicDerived : public dynamicBase
{
public:
	int Get() override { return 1; }
	int Get2() { return 2; }
};

class TestClass
{
public:
	int Get() { return 3; }
};

TEST(TypeCastingTest, DynamicCast)
{
	dynamicBase* base = new dynamicDerived();
	dynamicDerived* derived = dynamic_cast<dynamicDerived*>(base);
	TestClass* test = dynamic_cast<TestClass*>(base);

	EXPECT_EQ(2, derived->Get2());
	EXPECT_EQ(nullptr, test);

	delete base;
}
