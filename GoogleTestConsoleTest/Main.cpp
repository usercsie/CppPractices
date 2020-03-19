// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "gtest/gtest.h"


#include <string>
//#include "ConcurrentWrapper.h"
#include <vector>
#include <future>
#include <cctype>

//int Compute(int iIn)
//{
//	std::this_thread::sleep_for(std::chrono::seconds(iIn));
//	return iIn;
//}

//int main(int argc, char **argv)
//{			
//	std::packaged_task<int()> task([]() { return 7; });
//	std::future<int> f1 = task.get_future(); 
//	std::thread(std::move(task)).detach(); 
//	
//	std::future<int> f2 = std::async(std::launch::async, Compute, 2);
//	
//	std::promise<int> p;
//	std::future<int> f3 = p.get_future();
//	std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();
//
//	std::cout << "Waiting..." << std::flush;
//	f1.wait();
//	f2.wait();
//	f3.wait();
//	std::cout << "Done!\nResults are: "
//		<< f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
//
//	system("Pause");	
//}

//void uppercase(char& c)
//{
//	c = static_cast<char>(std::toupper(c));
//}
//
//void lowercase(char& c)
//{
//	c = static_cast<char>(std::tolower(c));
//}
//int main(int argc, char **argv)
//{
//	XYZCore::ConcurrentWrapper<std::string> cs{ "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLl\n" };
//
//	std::vector<std::future<void>> v1;
//	std::vector<std::future<void>> v2;
//	std::vector<std::future<void>> v3;
//
//	for (int i = 0; i < 5; ++i)
//	{
//		v1.push_back(
//			std::async(std::launch::async,
//				[&cs, i] {
//			cs([&i](std::string& s) {
//				for (auto& c : s) uppercase(c);
//			});
//			cs([](const std::string& s) { std::cout << s; });
//		}
//			)
//		);
//		v2.push_back(
//			std::async(std::launch::async,
//				[&cs, i] {
//			cs([&i](std::string& s) {
//				for (auto& c : s) lowercase(c);
//			});
//			cs([](const std::string& s) { std::cout << s; });
//		}
//			)
//		);
//	}
//
//	for (auto& fut : v1) fut.wait();
//	for (auto& fut : v2) fut.wait();
//	std::cout << "Done\n";
//}

//template <typename Fun, typename T>
//void promise_set_value(std::promise<void>& prom, Fun& f, T& t)
//{
//	f(t);
//	prom.set_value();
//}
//
//int main(int argc, char **argv)
//{	
//	XYZCore::ConcurrentWrapper<std::string> cs;
//
//	std::promise<void> pms;
//	std::future<void> f = pms.get_future();
//	int i = 0;
//
//
//
//	cs([i](std::string &s)
//	{
//		s += std::to_string(i);
//		s += "\n";	
//		std::cout << s;
//	});		
//	//std::vector<std::future<void>> v;
//
//	//for (int i = 0; i < 1; ++i)
//	//{
//	//std::promise<void> pms;
//	//std::future<void> f = pms.get_future();
//	//	std::future<void> f = std::async(std::launch::async, Action, 1, std::ref(cs));
//	//	f.wait();
//	//	v.push_back(f);
//	//		std::async(std::launch::async,
//	//			[&, i] 
//	//			{
//	///*				std::string s = std::to_string(i);
//	//				s += "\n";
//	//				std::cout << "Th: " << std::this_thread::get_id() << "\n" << s;*/
//	//				cs([&i](std::string& s) 
//	//				{
//	//					std::this_thread::sleep_for(std::chrono::seconds(2));
//	//					s += std::to_string(i);
//	//					s += std::to_string(i);
//	//					s += std::to_string(i);
//	//					s += "\n";
//	//					
//	//				});
//	//				cs([](const std::string& s) 
//	//				{
//	//					std::cout <<"Th: " << std::this_thread::get_id() << "\n" << s;
//	//				});
//	//			}
//	//		)
//	//	);
//	//}
//
//	/*for (auto& fut : v) 
//		fut.wait();*/
//	std::cout << "Done\n";
//
//	system("pause");
//}

int main(int argc, char **argv)
{	
	::testing::FLAGS_gtest_filter = "cpplinqTest.*";
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
