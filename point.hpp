//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Point)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once



namespace aului {
	template <typename T>
	struct Point {
		T x, y;

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
	inline Point<T> to_point(const POINT& pt)
	{
		return { (T)pt.x, (T)pt.y };
	}

	template <typename T>
	inline double distance(const Point<T>& pt1, const Point<T>& pt2)
	{
		return std::sqrt(std::pow(pt2.x - pt1.x, 2) + std::pow(pt2.y - pt1.y, 2));
	}
}