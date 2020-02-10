// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "gtest/gtest.h"


#include <string>
#include "ConcurrentWrapper.h"
#include <vector>
#include <future>

int main(int argc, char **argv)
{		
	XYZCore::ConcurrentWrapper<std::string> cs{ "Start\n" };

	std::vector<std::future<void>> v;

	for (int i = 0; i < 5; ++i)
	{
		v.push_back(std::async
			(
				std::launch::async,
				[&, i] 
				{
					cs([&i](std::string& s) 
					{
						s += std::to_string(i) + std::to_string(i) + std::to_string(i);
						s += "\n";
					});
					cs([](const std::string& s) 
					{ 
						std::cout << s; 
					});
				}
			)
		);
	}

	//for (auto& fut : v) 
	//	fut.wait();
	std::cout << "Done\n";


	::testing::FLAGS_gtest_filter = "ConcurrentQueue.*";
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
