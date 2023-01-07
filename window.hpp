//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Window)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"



namespace aului {
    class Window {
    protected:
        static LRESULT CALLBACK wndproc_static(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual LRESULT		wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	public:
        static constexpr int COMMAND_REDRAW = 0xffff;
		HWND hwnd;

		BOOL				create(
            HINSTANCE   hinst,
			HWND		hwnd_parent,
			LPCTSTR		class_name,
			WNDPROC		wndproc,
			LONG		window_style,
			LONG		class_style,
			const RECT& rect,
			LPVOID		lp_param
		);

		virtual void		move(const RECT& rect) const;
		void				redraw() const;
		BOOL				close() const;
		BOOL				show() const;
		BOOL				hide() const;
    };


    // Create Window
    inline BOOL Window::create(
        HINSTANCE   hinst,
        HWND		hwnd_parent,
        LPCTSTR		class_name,
        WNDPROC		wndproc,
        LONG		window_style,
        LONG		class_style,
        const RECT&	rect,
        LPVOID		lp_param)
    {
        WNDCLASSEX tmp;
        tmp.cbSize = sizeof(tmp);
        tmp.style = CS_HREDRAW | CS_VREDRAW | class_style;
        tmp.lpfnWndProc = wndproc;
        tmp.cbClsExtra = 0;
        tmp.cbWndExtra = 0;
        tmp.hInstance = hinst;
        tmp.hIcon = NULL;
        tmp.hCursor = LoadCursor(NULL, IDC_ARROW);
        tmp.hbrBackground = NULL;
        tmp.lpszMenuName = NULL;
        tmp.lpszClassName = class_name;
        tmp.hIconSm = NULL;

        if (::RegisterClassEx(&tmp)) {
            hwnd = ::CreateWindowEx(
                NULL,
                class_name,
                NULL,
                WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | window_style,
                rect.left,
                rect.top,
                rect.right - rect.left,
                rect.bottom - rect.top,
                hwnd_parent,
                NULL,
                hinst,
                lp_param
            );
            if (hwnd != nullptr)
                return TRUE;
        }
        return FALSE;
    }


    // Move Window
    inline void Window::move(const RECT& rect) const
    {
        ::MoveWindow(
            hwnd,
            std::min(rect.left, rect.right),
            std::min(rect.top, rect.bottom),
            std::abs(rect.right - rect.left),
            std::abs(rect.bottom - rect.top),
            TRUE
        );
    }

    // Redraw
    inline void aului::Window::redraw() const
    {
        ::PostMessage(hwnd, WM_COMMAND, COMMAND_REDRAW, 0);
    }

    // Show
    inline BOOL aului::Window::show() const
    {
        return ::ShowWindow(hwnd, SW_SHOW);
    }

    // Hide
    inline BOOL aului::Window::hide() const
    {
        return ::ShowWindow(hwnd, SW_HIDE);
    }

    // Close
    inline BOOL aului::Window::close() const
    {
        return ::DestroyWindow(hwnd);
    }

    // Window Procedule (Static)
    inline LRESULT CALLBACK aului::Window::wndproc_static(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        Window* app = (Window*)::GetWindowLongPtr(hwnd, GWLP_USERDATA);

        // 取得できなかった(ウィンドウ生成中)場合
        if (!app) {
            if (msg == WM_CREATE) {
                app = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;

                if (app) {
                    ::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)app);
                    return app->wndproc(hwnd, msg, wparam, lparam);
                }
            }
            return ::DefWindowProc(hwnd, msg, wparam, lparam);
        }
        // 取得できた場合(ウィンドウ生成後)
        else {
            return app->wndproc(hwnd, msg, wparam, lparam);
        }
    }

    // Window Procedure
    inline LRESULT aului::Window::wndproc(HWND hw, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        return ::DefWindowProc(hw, msg, wparam, lparam);
    }
}