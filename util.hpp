#pragma once

#include "common.hpp"



namespace aului {
	template <typename T>
	inline bool in_range(T val, T min, T max, bool equal)
	{
		if (val >= min && val <= max) {
			if (val == min || val == max)
				return equal;
			else
				return true;
		}
		else
			return false;
	}


	inline std::vector<std::string> split(const std::string& s, TCHAR c)
	{
		std::vector<std::string> elems;
		std::string item;
		for (TCHAR ch : s) {
			if (ch == c) {
				if (!item.empty()) {
					elems.emplace_back(item);
					item.clear();
				}
			}
			else item += ch;
		}
		if (!item.empty())
			elems.emplace_back(item);

		return elems;
	}
}