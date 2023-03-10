//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Rectangle)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"



namespace aului {
	template <typename T>
	// Rectangle
	struct Rectangle {
		T left, top, right, bottom;

		inline Rectangle(T l=0, T t=0, T r=0, T b=0) :
			left(l),
			top(t),
			right(r),
			bottom(b)
		{}

		template <typename U>
		void convert_to(Rectangle<U>* r)
		{
		    r->left = (U)left;
			r->top = (U)top;
			r->right = (U)right;
			r->bottom = (U)bottom;
		}
	};


	// Rectangle for Window
	struct Window_Rectangle {
		RECT rect;

        void set(const RECT& rc);
		void set(int left, int top, int right, int bottom);
		void set_margin(int left, int top, int right, int bottom);
		void divide(LPRECT rects_child[], float weights[], int n) const;
		void client_to_screen(HWND hwnd);
		void screen_to_client(HWND hwnd);
	};


	// Initialize (1)
	inline void Window_Rectangle::set(const RECT& rc)
	{
		rect = rc;
	}

	// Initialize (2)
	inline void Window_Rectangle::set(int left, int top, int right, int bottom)
	{
		rect = { left, top, right, bottom };
	}

	// Divide a rectangle into n child rectangles
	inline void Window_Rectangle::divide(LPRECT rects_child[], float weights[], int n) const
	{
		int width_parent = rect.right - rect.left;
		int width_child = width_parent / n;
		float weights_sum = 0;
		std::vector<float> list_weights_sum;
		int left, right;

		if (weights) {
			for (int i = 0; i < n; i++) {
				weights_sum += weights[i];
				list_weights_sum.emplace_back(weights_sum);
			}
		}

		for (int i = 0; i < n; i++) {
			if (weights) {
				left = (int)(width_parent * ((i == 0) ? 0 : list_weights_sum[i - 1]) / weights_sum);
				right = (int)(width_parent * list_weights_sum[i] / weights_sum);
			}
			else {
				left = i * width_child;
				right = (i + 1) * width_child;
			}
			rects_child[i]->left = rect.left + left;
			rects_child[i]->right = rect.left + right;
			rects_child[i]->top = rect.top;
			rects_child[i]->bottom = rect.bottom;
		}
	}

	// Set Margin
	inline void Window_Rectangle::set_margin(int left, int top, int right, int bottom)
	{
		rect.left += left;
		rect.top += top;
		rect.right -= right;
		rect.bottom -= bottom;

		if (rect.left > rect.right)
			rect.left = rect.right = (rect.left + rect.right) / 2;
		if (rect.top > rect.bottom)
			rect.top = rect.bottom = (rect.top + rect.bottom) / 2;
	}

	// Client to Screen
	inline void Window_Rectangle::client_to_screen(HWND hwnd)
	{
		POINT pt[2];
		pt[0] = {
			rect.left,
			rect.top
		};
		pt[1] = {
			rect.right,
			rect.bottom
		};
		::ClientToScreen(hwnd, &pt[0]);
		::ClientToScreen(hwnd, &pt[1]);
		rect = {
			pt[0].x, pt[0].y,
			pt[1].x, pt[1].y,
		};
	}

	// Screen to Client
	inline void Window_Rectangle::screen_to_client(HWND hwnd)
	{
		POINT pt[2];
		pt[0] = {
			rect.left,
			rect.top
		};
		pt[1] = {
			rect.right,
			rect.bottom
		};
		::ScreenToClient(hwnd, &pt[0]);
		::ScreenToClient(hwnd, &pt[1]);
		rect = {
			pt[0].x, pt[0].y,
			pt[1].x, pt[1].y,
		};
	}
}