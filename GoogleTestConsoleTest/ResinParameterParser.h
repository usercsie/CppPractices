#pragma once

#include "FileOper.h"

namespace XYZNobel
{
	class ResinParameterParser
	{
	public:
		int Read(std::string fullFileName)
		{
			if (XYZCore::FileOper::FileExisted(fullFileName) == false)
			{
				return 1;//file has not existed.
			}

			std::vector<std::string> lines = XYZCore::FileOper::ReadAllLines(fullFileName);


			return 0;
		}

		int GetLevelCount()
		{
			return _MaxWidth.size();
		}
		int GetMaxWidth(int level)
		{
			return level < GetLevelCount() ? _MaxWidth[level] : -1;
		}
		int GetAngle(int level)
		{
			return level < GetLevelCount() ? _MaxAngle[level] : -1;
		}
		int GetTotalArea(int level)
		{
			return level < GetLevelCount() ? _MaxTotalArea[level] : -1;
		}
		int GetMaxDistance(int level)
		{
			return level < GetLevelCount() ? _MaxDistance[level] : -1;
		}
	private:
		std::vector<int> _MaxWidth;
		std::vector<int> _MaxAngle;
		std::vector<int> _MaxTotalArea;
		std::vector<int> _MaxDistance;

		void RemoveCommentLines(std::vector<std::string> &lines)
		{

		}
	};
}