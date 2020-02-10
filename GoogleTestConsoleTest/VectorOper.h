#pragma once
#include <string>
#include <algorithm>
#include <vector>

namespace XYZCore
{
	class VectorOper
	{
	public:
		//static int FindString(const std::vector<std::string> &elements, const std::string &str)
		//{
		//	std::vector<std::string>::const_iterator it = std::find(elements.begin(), elements.end(), str);
		//}
		static int FindString(const std::vector<std::string>  &elements, const std::string  &element)
		{
			int id = -1;
			auto it = std::find(elements.begin(), elements.end(), element);

			if (it != elements.end())
			{
				id = distance(elements.begin(), it);
			}

			return id;
		}
	};
}