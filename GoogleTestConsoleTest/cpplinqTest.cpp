#include "gtest/gtest.h"
#include "cpplinq.hpp"

using namespace cpplinq;

TEST(cpplinqTest, where)
{
	int ints[] = { 3,1,4,1,5,9,2,6,5,4 };

	auto result = from_array(ints) 
		>> where([](int i) {return i == 1; })
		>> to_vector();

	EXPECT_EQ(2, result.size());
}

TEST(cpplinqTest, select)
{
	int ints[] = { 3,1,4,1,5,9,2,6,5,4 };

	auto result = from_array(ints)
		>> select([](int i) {return i + 1; })
		>> to_vector();

	EXPECT_EQ(10, result.size());
	for (int n = 0; n < result.size(); n++)
	{
		EXPECT_EQ(result[n], ints[n] + 1);
	}
}

TEST(cpplinqTest, Distinct)
{
	int ints[] = { 3,1,4,1,5,9,2,6,5,4 };
	auto result = from_array(ints)
		>> distinct()
		>> to_vector();

	EXPECT_EQ(7, result.size());
}

TEST(cpplinqTest, Order)
{
	int ints[] = { 2,3,4,1 };
	auto result = from_array(ints)
		>> orderby([](int i) {return i; })
		>> to_vector();

	for (int n = 0; n < 4; n++)
	{
		EXPECT_EQ(n + 1, result[n]);
	}
}

TEST(cpplinqTest, Count)
{
	int ints[] = { 2,3,4,1,2 };
	auto result = from_array(ints)
		>> where([](int i) {return i == 2; })
		>> count();

	EXPECT_EQ(2, result);

}

TEST(cpplinqTest, Take)
{
	int ints[] = { 1,2,3,4,5,6,7 };
	auto result = from_array(ints)
		>> take(5)
		>> to_vector();

	EXPECT_EQ(5, result.size());
	for (int n = 0; n < result.size(); n++)
	{
		EXPECT_EQ(ints[n], result[n]);
	}
}

TEST(cpplinqTest, where_sum)
{
	int ints[] = { 3,1,4,1,5,9,2,6,5,4 };

	auto result = from_array(ints)
		>> where([](int i) {return i % 2 == 0; })  // Keep only even numbers
		>> sum()                               // Sum remaining numbers
		;

	EXPECT_EQ(16, result);
}

//struct customer
//{
//	std::size_t     id;
//	std::string     first_name;
//	std::string     last_name;
//	customer(std::size_t _id, std::string _first_name, std::string _last_name)
//	{
//		id = _id;
//		first_name = _first_name;
//		last_name = _last_name;
//	}
//};
//
//struct customer_address
//{
//	std::size_t     id;
//	std::size_t     customer_id;
//	std::string     country;
//	customer_address(std::size_t _id, std::size_t _customer_id, std::string _country)
//	{
//		id = _id;
//		customer_id = _customer_id;
//		country = _country;
//	}
//};
//
//TEST(cpplinqTest, Join)
//{
//	customer customers[] =
//	{
//		customer(1 , "Bill"    , "Gates"),
//		customer(2 , "Steve"   , "Jobs"),
//		customer(3 , "Richard" , "Stallman"),
//		customer(4 , "Linus"   , "Torvalds"),
//	};
//
//	customer_address customer_addresses[] =
//	{
//		customer_address(1, 1, "USA"),
//		customer_address(2, 4, "Finland"),
//		customer_address(3, 4, "USA"),
//	};
//
//	auto result =
//		from_array(customers)
//		>> join(
//			from_array(customer_addresses),
//			[=](customer const& c) {return c.id; },
//			[=](customer_address const & ca) {return ca.customer_id; },
//			[=](customer const & c, customer_address const & ca) {return std::make_pair(c, ca); }
//		) >> to_vector();
//}