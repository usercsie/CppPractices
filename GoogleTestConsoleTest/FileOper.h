#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace XYZCore
{
	class FileOper
	{
	public:

		static bool CreateFile(std::string fileName)
		{
			std::ofstream fs(fileName, std::ios::app);

			if (fs)
				return true;
			else
				return false;
		}

		static bool CreateFile(std::wstring fileName)
		{
			std::ofstream fs(fileName, std::ios::app);

			if (fs)
				return true;
			else
				return false;
		}

		static int DeleteFile(std::string fileName)
		{
			return std::remove(fileName.c_str());
		}

		static int DeleteFile(std::wstring fileName)
		{
			return _wremove(fileName.c_str());
		}

		static void WriteAllBytes(std::string fileName, const char* data, size_t size)
		{
			std::ofstream fs;
			fs.open(fileName.c_str(), std::ios_base::binary);
			fs.write(data, size);
		};

		static void WriteAllText(std::string fileName, const std::string context)
		{
			std::ofstream fs;
			fs.open(fileName.c_str());
			fs.write(context.c_str(), context.length());
		}

		static void WriteAllLines(std::string fileName, const std::vector<std::string> content)
		{
			std::ofstream fs;
			fs.open(fileName.c_str());

			if (fs)
			{
				for (auto line : content)
				{
					fs << line << std::endl;
				}
			}
		}

		static std::vector<unsigned char> ReadAllBytes(std::string fileName)
		{
			std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
			std::ifstream::pos_type pos = ifs.tellg();

			std::vector<unsigned char> result((int)pos);

			ifs.seekg(0, std::ios::beg);
			ifs.read((char*)result.data(), pos);

			return result;
		}

		static std::string ReadAllText(std::string fileName)
		{
			std::ifstream ifs(fileName);
			std::string str;

			if (ifs)
			{
				ifs.seekg(0, std::ios::end);
				str.reserve(ifs.tellg());
				ifs.seekg(0, std::ios::beg);
				str.assign(std::istreambuf_iterator<char>(ifs),
					std::istreambuf_iterator<char>());
			}

			return str;
		}

		static std::vector<std::string> ReadAllLines(std::string fileName)
		{
			std::ifstream ifs(fileName);

			std::vector<std::string> lines;

			if (ifs)
			{
				for (std::string line; std::getline(ifs, line); /**/)
				{
					lines.push_back(line);
				}
			}

			return lines;
		}

		static bool FileExisted(std::wstring fullFileName)
		{
			std::ifstream ifile;
			ifile.open(fullFileName.c_str());
			if (ifile)
				return true;
			else
				return false;
		}

		static bool FileExisted(std::string fullFileName)
		{
			std::ifstream ifile;
			ifile.open(fullFileName.c_str());
			if (ifile)
				return true;
			else
				return false;
		}
	};
}