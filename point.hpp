//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Point)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once



namespace win32ui {
	template <typename T>
	struct Point {
		T x, y;

		template<typename U>
		inline Point<U> to()
		{
			return { (U)x, (U)y };
		}
	};
}