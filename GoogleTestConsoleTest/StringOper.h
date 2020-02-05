#pragma once
#include <string>
#include <algorithm> 
#include <cctype>
#include <vector>

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

		static std::vector<std::string> Split(std::string s, std::string delimiter)
		{
			std::vector<std::string> tokens;

			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) 
			{
				token = s.substr(0, pos);				
				tokens.push_back(token);
				s.erase(0, pos + delimiter.length());
			}
			if (tokens.size() > 0 && s.length() > 0)
			{
				tokens.push_back(s.substr(0, s.length()));
			}
			return tokens;
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

		static void CutEnd(std::string &s, char c)
		{
			for (auto i = s.rbegin(); i != s.rend(); ++i)
			{
				if (*i == c)
				{
					s.pop_back();
				}
				else
					break;
			}
		}
	};	
}