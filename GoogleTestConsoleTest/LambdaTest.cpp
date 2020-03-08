#include "gtest\gtest.h"

auto makeWalrus(const std::string name)
{
	return [=]() -> std::string
	{
		//std::cout << "I am a walrus, my name is " << name << std::endl;
		return name;
	};
}

TEST(Lambda, DanglingCapturedVariables)
{
	auto sayName{ makeWalrus("Roofus") };

	std::string result = sayName();

	EXPECT_EQ("Roofus", result);
}