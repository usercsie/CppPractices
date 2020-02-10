#pragma once
#include <string>

namespace XYZCore
{
	class PathOper
	{
	public:
		static std::string GetFileName(std::string filePath, char seperator = '\\')
		{
			std::size_t sepPos = filePath.rfind(seperator);

			if (sepPos != std::string::npos)
			{
				int size = filePath.size() - sepPos - 1;
				return filePath.substr(sepPos + 1, size);
			}
			return filePath;
		}

		static std::string GetFileNameWithoutExtension(std::string filePath, char seperator = '\\')
		{
			std::string fileName = GetFileName(filePath, seperator);

			std::size_t dotPos = fileName.rfind('.');
			if (dotPos != std::string::npos)
			{
				return fileName.substr(0, fileName.length() - dotPos - 1);
			}

			return fileName;			
		}
	};
}