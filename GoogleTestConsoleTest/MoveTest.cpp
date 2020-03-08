#include "MoveTest.h"

std::vector<int> GetVector()
{
	std::vector<int> array
	{
		1,2,3,4,5,7,8,9,10
	};

	return array;
}

TEST(MoveTest, returnVector)
{
	std::vector<int> array = GetVector();
	std::vector<int> array2 = array;

	EXPECT_EQ(array2, array);

	std::vector<int> array3 = std::move(array);
	
	EXPECT_EQ(array3, array2);
	EXPECT_EQ(0, array.size());
}

template<typename T>
class MyVector
{
public:
	std::vector<T> Inst;
	MyVector()
	{
	}
	MyVector(const MyVector &r)
	{
		Inst = r.Inst;
		std::cout << "copy construct" << std::endl;
	}
	MyVector& operator = (const MyVector& r)
	{
		Inst = r.Inst;
		std::cout << "copy assignment" << std::endl;
	}
	//MyVector(MyVector &&r)
	//{
	//	Inst = std::move(r.Inst);
	//	std::cout << "move construct" << std::endl;
	//}
	//MyVector& operator = (MyVector&& r)
	//{
	//	std::cout << "move assignment" << std::endl;
	//}
	~MyVector() {}
};

MyVector<int> GetMyVector()
{
	MyVector<int> array;
	
	array.Inst.push_back(0);

	return array;
}

TEST(MoveTest, returnMyVector)
{
	MyVector<int> array = GetMyVector();
	MyVector<int> array2 = array;

	EXPECT_EQ(array2.Inst.size(), 1);
	EXPECT_EQ(array.Inst.size(), 1);
}

TEST(MoveTest, defaultMove)
{
	MyVector<int> array4;
	array4.Inst.push_back(0);
	MyVector<int> array5 = std::move(array4);
	EXPECT_EQ(1, array5.Inst.size());
	EXPECT_EQ(1, array4.Inst.size());
}

class Fraction
{
public:
	int m_numerator;
	int m_denominator;

	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.m_numerator << '/' << f1.m_denominator;
		return out;
	}
};

int LRerence(const int &value)
{
	return value;
}

TEST(MoveTest, RValueReferToTempObject)
{
	int n = 10;
	EXPECT_EQ(10, LRerence(std::move(n)));

	const Fraction& lref{ Fraction{3, 5} };
	EXPECT_EQ(3, lref.m_numerator);
	EXPECT_EQ(5, lref.m_denominator);

	auto &&rref{ Fraction{ 3, 5 } };

	EXPECT_EQ(3, rref.m_numerator);
	EXPECT_EQ(5, rref.m_denominator);	
}


TEST(MoveTest, PerfectForwarding)
{

}