#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
namespace XYZCore
{
	class DirectoryOper
	{
		static bool Create(std::string path)
		{
			std::wstring ws(path.begin(), path.end());
			return Create(ws);
		}
		static bool Create(std::wstring path)
		{
			if (CreateDirectory(path.c_str(), NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		//static bool Exists(std::string path)
		//{
		//	std::wstring ws(path.begin(), path.end());
		//	return Exists(ws);
		//}
		static bool Exists(std::string path)
		{
			DWORD ftyp = GetFileAttributesA(path.c_str());

			if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
				return true;

			return false;
		}


		static std::vector<std::string> GetFiles(std::string path)
		{

		}

		static std::vector<std::string> GetFiles(std::string path, std::string searchPattern)
		{

		}
	};
};