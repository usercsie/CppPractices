#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <filesystem>

namespace XYZCore
{
	class DirectoryOper
	{
	public:
		static bool Create(std::string path)
		{
			//std::filesystem::path tmp(path);

			//if (Exists(tmp) == true)
			//	return true;

			//return std::filesystem::create_directory(path);
			if (CreateDirectoryA(path.c_str(), NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		static bool Create(std::wstring path)
		{
			//std::filesystem::path tmp(path);

			//if (Exists(tmp) == true)
			//	return true;

			//return std::filesystem::create_directory(path);
			if (CreateDirectoryW(path.c_str(), NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static bool Exists(std::string path)
		{
			//std::filesystem::path tmp(path);
			//return std::filesystem::exists(tmp);
			DWORD ftyp = GetFileAttributesA(path.c_str());

			if (ftyp == INVALID_FILE_ATTRIBUTES)
				return false;  //something is wrong with your path!

			if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
				return true;   // this is a directory!

			return false;    // this is not a directory!
		}
		static bool Exists(std::wstring path)
		{
			/*std::filesystem::path tmp(path);
			return std::filesystem::exists(tmp);*/
			DWORD ftyp = GetFileAttributesW(path.c_str());

			if (ftyp == INVALID_FILE_ATTRIBUTES)
				return false;  //something is wrong with your path!

			if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
				return true;   // this is a directory!

			return false;    // this is not a directory!
		}

		static bool Delete(std::string path)
		{
			return RemoveDirectoryA(path.c_str());
		}
		static bool Delete(std::wstring path)
		{
			return RemoveDirectoryW(path.c_str());
		}

		/*		static std::vector<std::string> GetFiles(std::string path)
				{
					std::filesystem::path str(path);
				}

				static std::vector<std::string> GetFiles(std::string path, std::string searchPattern)
				{
				}	*/
	};
};