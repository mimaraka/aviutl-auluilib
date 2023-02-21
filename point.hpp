//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Point)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"



namespace aului {
	template <typename T>
	struct Point {
		T x, y;

		inline bool operator == (const Point<T>& pt) const
		{
			return this->x == pt.x && this->y == pt.y;
		}

		template <typename PtType>
		inline Point<T> operator + (const PtType& pt) const
		{
			return {
				this->x + (T)pt.x,
				this->y + (T)pt.y
			};
		}

		template <typename PtType>
		inline Point<T> operator - (const PtType& pt) const
		{
			return {
				this->x - (T)pt.x,
				this->y - (T)pt.y
			};
		}

		inline Point(T x_=0, T y_=0) :
			x(x_),
			y(y_)
		{}

		inline Point(const POINT& pt) :
			x((T)pt.x),
			y((T)pt.y)
		{}

		template<typename U>
		inline Point<U> to()
		{
			return { (U)x, (U)y };
		}

		inline POINT to_win32_point()
		{
			return { (LONG)x, (LONG)y };
		}
	};

	template <typename T>
	inline double distance(const Point<T>& pt1, const Point<T>& pt2)
	{
		return std::sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
	}

	template <class Pt>
	inline double distance(const Pt& pt1, const Pt& pt2)
	{
		return std::sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
	}
}