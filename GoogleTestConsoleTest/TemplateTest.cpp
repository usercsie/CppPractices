#include <iostream>
#include "gtest/gtest.h"

//function template
template<class T> T Add(T a, T b)
{
	return a + b;
}
TEST(TemplateTest, basicfunctionTemplate)
{
	EXPECT_EQ(5, Add(2, 3));	
	EXPECT_EQ(5.4, Add<double>(2, 3.4));
	EXPECT_EQ(5.4, Add(2.1, 3.3));
}

template <class T>
class Pair
{
public:
	T Param1;
	T Param2;

	Pair(T p1, T p2)
	{
		Param1 = p1;
		Param2 = p2;
	}
};
TEST(TemplateTest, basicClassTemplate)
{
	Pair<int> p(1, 2);
	EXPECT_EQ(1, p.Param1);
	EXPECT_EQ(2, p.Param2);

	Pair<double> p2(0.5, 0.6);
	EXPECT_EQ(0.5, p2.Param1);	
	EXPECT_EQ(0.6, p2.Param2);
}

//template<class T=int, int N=10> //indicate the default type and value.
template<class T=int, int N=10>
class Array
{
	T _Item[N];
public:
	void Set(int x, T value)
	{
		_Item[x] = value;
	}
	T Get(int x)
	{
		return _Item[x];
	}
};
TEST(TemplateTest, ClassTemplateWithArgs)
{	
	Array<int, 10> ar;
	ar.Set(1, 10);
	EXPECT_EQ(10, ar.Get(1));

	std::unique_ptr<Array<int, 10>> ptr = std::make_unique < Array<int, 10>>();
	ptr->Set(2, 5);
	EXPECT_EQ(5, ptr->Get(2));
}

enum eColor { none = 0, red, green, blue };
class Color
{
public:
	Color(eColor color)
	{
		_Color = color;
	};
	void SetColor(eColor color)
	{
		_Color = color;
	};
	std::string ToString()
	{
		switch (_Color)
		{
		case red:
			return "Red";
		case green:
			return "Green";
		case blue:
			return "Blue";
		case none:
		default:
			return "none";
		}
	}
	eColor GetColor() { return _Color; };	

protected:
	eColor _Color;
};

template<class T>
class Shape : public Color
{
public:
	T PosX;
	T PosY;	

	Shape(T x, T y, eColor color)
		: Color::Color(color)
	{
		PosX = x;
		PosY = y;		
	}
	Shape(eColor color) : Color::Color(color)
	{
		this->PosX = const_cast<T>(0);
		this->PosY = const_cast<T>(0);		
	}
};

template<class T>
class Circle : public Shape<T>
{
public:
	T Radius;

	Circle(T x, T y, eColor color, T radius)
		: Shape<T>::Shape(x, y, color)
	{
		Radius = radius;
	}
	Circle(eColor color) : Shape<T>::Shape(color)
	{
		Radius = const_cast<T>(1);
	}
};
TEST(TemplateTest, TemplateInheritance)
{
	Circle<float> inst(1.0, 2.0, eColor::red, 5.0);

	EXPECT_EQ(1.0, inst.PosX);
	EXPECT_EQ(2.0, inst.PosY);
	EXPECT_EQ(5.0, inst.Radius);
}

//class Rectangle : public Shape<int>
//{
//public:
//	Rectangle(int x, int y, eColor color) 
//		: Shape<int>::Shape(x, y, color)
//	{
//	}
//	Rectangle(eColor color)
//		: Shape<int>::Shape(color)
//	{
//
//	}
//};