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
}