#pragma once

#include "FileOper.h"
#include "StringOper.h"
#include "VectorOper.h"

namespace XYZNobel
{
	enum class ResinParserError
	{
		FileNotFound = 1,
		SlicingJudgeLevelTableFormatError,
		PowerTableFormatError
	};
	class ResinParameterParser
	{
	public:
		int Read(std::string fullFileName)
		{
			if (XYZCore::FileOper::FileExisted(fullFileName) == false)
			{
				return (int)ResinParserError::FileNotFound;
			}

			Reset();

			std::vector<std::string> lines = XYZCore::FileOper::ReadAllLines(fullFileName);
			CompactLines(lines);			

			if (ReadJudgeLevelTable(lines) == false)
			{
				return (int)ResinParserError::SlicingJudgeLevelTableFormatError;
			}

			if (ReadPowerTable(lines) == false)
			{
				return (int)ResinParserError::PowerTableFormatError;
			}

			return 0;
		}

		std::vector<int> GetMaxWidth(std::string version, std::string type, std::string layerHeight, std::string quality)
		{
			std::string key = ToKey(version, type, layerHeight, quality);
			if (_MaxWidth.find(key) == _MaxWidth.end())
				return std::vector<int>();
			else
				return _MaxWidth[key];
		}
		std::vector<int> GetAngle(std::string version, std::string type, std::string layerHeight, std::string quality)
		{
			std::string key = ToKey(version, type, layerHeight, quality);
			if (_MaxAngle.find(key) == _MaxAngle.end())
				return std::vector<int>();
			else
				return _MaxAngle[key];
		}
		std::vector<int> GetTotalArea(std::string version, std::string type, std::string layerHeight, std::string quality)
		{
			std::string key = ToKey(version, type, layerHeight, quality);
			if (_MaxTotalArea.find(key) == _MaxTotalArea.end())
				return std::vector<int>();
			else
				return _MaxTotalArea[key];
		}
		std::vector<int> GetMaxDistance(std::string version, std::string type, std::string layerHeight, std::string quality)
		{
			std::string key = ToKey(version, type, layerHeight, quality);
			if (_MaxDistance.find(key) == _MaxDistance.end())
				return std::vector<int>();
			else
				return _MaxDistance[key];
		}		
		std::string GetPowerTable(std::string version, std::string type, std::string layerHeight, std::string quality, std::string level)
		{
			std::string key = ToKey(version, type, layerHeight, quality, level);
			if (_PowerTables.find(key) == _PowerTables.end())
				return std::string();
			else
				return _PowerTables[key];
		}

	private:
		std::map<std::string, std::vector<int>> _MaxWidth;
		std::map<std::string, std::vector<int>> _MaxAngle;
		std::map<std::string, std::vector<int>> _MaxTotalArea;
		std::map<std::string, std::vector<int>> _MaxDistance;
		std::map<std::string, std::string> _PowerTables;

		//Remove commands and empty lines.
		void CompactLines(std::vector<std::string> &lines)
		{
			lines.erase(std::remove_if(lines.begin(), lines.end(), [](std::string const &i)
			{
				return XYZCore::StringOper::IsEmptyOrSpace(i) || i.front() == ';';
			}), lines.end());
		}

		bool ReadJudgeLevelTable(const std::vector<std::string> &lines)
		{
			int tableId = FindString(lines, "SlicingJudgeLevelTable");
			if (tableId == -1)
				return false;
			
			int numOfTable = std::stoi(lines[++tableId]);
			for (int n = 0; n < numOfTable; n++)
			{
				std::vector<std::string> items = SplitAndTrim(lines[++tableId], ",");
				std::string key = ToKey(items[1], items[2], items[3], items[4]);
				int numOfLevel = std::stoi(items[0]);
				std::vector<int> widths;
				std::vector<int> angles;
				std::vector<int> areas;
				std::vector<int> dists;
				for (int m = 0; m < numOfLevel; m++)
				{
					std::vector<std::string> ths = SplitAndTrim(lines[++tableId], ",");			
					widths.push_back(std::stoi(ths[0]));
					angles.push_back(std::stoi(ths[1]));
					areas.push_back(std::stoi(ths[2]));
					dists.push_back(std::stoi(ths[3]));
				}
				if (AddLevelTable(key, widths, angles, areas, dists) == false)
					return false;
			}

			return true;
		}

		bool ReadPowerTable(const std::vector<std::string> &lines)
		{
			int tableId = FindString(lines, "PowerTable");
			if (tableId == -1)
				return false;

			int numOfTable = std::stoi(lines[++tableId]);
			for (int n = 0; n < numOfTable; n++)
			{
				std::vector<std::string> items = SplitAndTrim(lines[++tableId], ",");
				std::string key = ToKey(items[0], items[1], items[2], items[3], items[4]);
				int parameterSize = std::stoi(items[5]);
				//parameter count is incorrect.
				if (parameterSize != items.size() - 6)
					return false;

				std::string p;
				for (int n = 6; n < items.size(); n++)
				{
					p += (items[n] + ",");
				}
				p = p.substr(0, p.length() - 1);//remove last ','

				if (AddPowerTable(key, p) == false)
					return false;
			}

			return true;
		}

		int FindString(const std::vector<std::string>  &elements, const std::string  &element)
		{
			int id = -1;
			for (auto e : elements)
			{
				id++;
				XYZCore::StringOper::EraseAll(e, '\t');
				XYZCore::StringOper::EraseAll(e, '\n');				
				if (e == element)
					return id;				
			}
			return -1;
		}

		std::string ToKey(std::string version, std::string type, std::string layerHeight, std::string quality)
		{
			return version + "-" + type + "-" + layerHeight + "-" + quality;
		}	

		std::string ToKey(std::string version, std::string type, std::string layerHeight, std::string quality, std::string level)
		{
			return version + "-" + type + "-" + layerHeight + "-" + quality + "-" + level;
		}

		std::vector<std::string> SplitAndTrim(std::string str, std::string del)
		{
			std::vector<std::string> tokens = XYZCore::StringOper::Split(str, del);
			for (std::string &s : tokens)
			{
				XYZCore::StringOper::TrimAll(s);			
			}
			return tokens;
		}

		void Reset()
		{
			_MaxWidth.clear();
			_MaxAngle.clear();
			_MaxTotalArea.clear();
			_MaxDistance.clear();

			_PowerTables.clear();
		}

		bool AddLevelTable(std::string key, std::vector<int> width, std::vector<int> angle, 
			std::vector<int> area, std::vector<int> distance)
		{
			//prevent duplicate
			auto it = _MaxWidth.find(key);
			if (it != _MaxWidth.end())
				return false;

			_MaxWidth.insert(std::pair<std::string, std::vector<int>>(key, width));
			_MaxAngle.insert(std::pair<std::string, std::vector<int>>(key, angle));
			_MaxTotalArea.insert(std::pair<std::string, std::vector<int>>(key, area));
			_MaxDistance.insert(std::pair<std::string, std::vector<int>>(key, distance));

			return true;
		}

		bool AddPowerTable(std::string key, std::string parameter)
		{
			if (_PowerTables.find(key) != _PowerTables.end())
				return false;

			_PowerTables.insert(std::pair<std::string, std::string>(key, parameter));

			return true;
		}
	};
}