//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Button)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "../common.hpp"



//namespace aului {
//    namespace control {
//        class Button : public Window {
//        public:
//            static constexpr int CONTENT_MAX_N = 128;
//            static constexpr int FLAG_DISABLED = 1 << 0;
//            static constexpr int FLAG_USE_ICON = 1 << 1;
//            enum Content_Type {
//                Null,
//                Icon,
//                String
//            };
//
//            int				    	id;
//            int					    status;
//
//            virtual BOOL	    	init(
//                HWND hwnd_p,
//                LPCTSTR cont,
//                LPCTSTR tooltip_lb,
//                Content_Type cont_type,
//                LPCTSTR ico_res_dark,
//                LPCTSTR ico_res_light,
//                LPCTSTR lb,
//                int ct_id,
//                const RECT& rect,
//                int flag
//            );
//            void			    	set_status(int flags);
//            
//        protected:
//            LPTSTR		      		icon_res_dark;
//            LPTSTR		    		icon_res_light;
//            Content_Type	    	content_type;
//            char				    content[CONTENT_MAX_N];
//            Direct2d_Paint_Object	paint_object;
//            HWND		    		hwnd_parent;
//            HWND		    		hwnd_tooltip;
//            TOOLINFO	    		tool_info;
//            bool			    	hovered, clicked, disabled;
//            TRACKMOUSEEVENT	    	tme;
//            HICON			    	icon_dark;
//            HICON			    	icon_light;
//            HFONT			    	font;
//            LPTSTR			    	tooltip_label;
//            int				    	flag_edge;
//
//            void			    	draw_content(COLORREF bg, RECT* rect_content, LPCTSTR content, bool change_color);
//            void				    draw_edge();
//            void				    set_font(int font_height, LPTSTR font_name);
//            virtual LRESULT		    wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//        };
//    }
//}