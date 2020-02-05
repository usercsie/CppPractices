#pragma once
#include <string>

namespace XYZCore
{
	class PathOper
	{
	public:
		static std::string GetFileName(std::string filePath, bool withExtension = true, char seperator = '\\')
		{
			// Get last dot position
			std::size_t dotPos = filePath.rfind('.');
			std::size_t sepPos = filePath.rfind(seperator);

			if (sepPos != std::string::npos)
			{
				int size = filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos);
				return filePath.substr(sepPos + 1, size);
			}
			return "";
		}
	};
}