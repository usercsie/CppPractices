#pragma once
#include <string>
#include <algorithm> 
#include <cctype>

namespace XYZCore
{
	class StringOper
	{
	public:
		static void TrimStart(std::string &s) 
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) 
			{
				return !std::isspace(ch);
			}));
		}
		static void TrimEnd(std::string &s) 
		{
			s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) 
			{
				return !std::isspace(ch);
			}).base(), s.end());
		}
		static void Trim(std::string &s) 
		{
			TrimStart(s);
			TrimEnd(s);
		}

		static void TrimAll(std::string &s)
		{
			s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
		}

		static bool IsEmptyOrSpace(std::string s)
		{
			TrimAll(s);
			EraseAll(s, ' ');
			return s.length() == 0;
		}

		static void EraseAll(std::string &s, char c)
		{
	//		std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
	//		s.erase(end_pos, s.end());
			s.erase(std::remove(s.begin(), s.end(), c), s.end());
		}
	};	
}