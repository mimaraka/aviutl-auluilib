//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Direct2D Paint)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"
#include "../../color.hpp"



namespace aului {
    class Direct2d_Paint_Object {
        public:
            ID2D1HwndRenderTarget* p_render_target;
            ID2D1SolidColorBrush* brush;
            RECT rect;

            Direct2d_Paint_Object() :
                p_render_target(nullptr),
                p_factory(nullptr),
                p_write_factory(nullptr),
                brush(nullptr),
                hwnd(NULL),
                rect({ NULL })
            {}

            virtual bool init(HWND hw, ID2D1Factory* p_fctry, IDWriteFactory* p_wfctry);
            virtual void exit();
            void resize();

            template <class Interface>
            void release(Interface** object);

        protected:
            ID2D1Factory* p_factory;
            IDWriteFactory* p_write_factory;
            IWICImagingFactory* p_image_factory;
            HWND hwnd;

            template <class Interface>
            bool is_safe(Interface** object);
    };


    // Initialize
    inline bool Direct2d_Paint_Object::init(HWND hw, ID2D1Factory* p_fctry, IDWriteFactory* p_wfctry)
    {
        HRESULT hresult;
        D2D1_RENDER_TARGET_PROPERTIES render_target_props;
        D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_render_target_props;
        D2D1_SIZE_U pixel_size;

        if (p_fctry == nullptr || p_wfctry == nullptr) return false;

        hwnd = hw;
        p_factory = p_fctry;
        p_write_factory = p_wfctry;

        ::GetClientRect(hw, &rect);

        pixel_size = {
            (unsigned)(rect.right - rect.left),
            (unsigned)(rect.bottom - rect.top)
        };

        render_target_props = D2D1::RenderTargetProperties();
        hwnd_render_target_props = D2D1::HwndRenderTargetProperties(hw, pixel_size);

        hresult = p_factory->CreateHwndRenderTarget(
            render_target_props,
            hwnd_render_target_props,
            &p_render_target
        );

        if (FAILED(hresult) || p_render_target == nullptr)
            return false;
        
        if (brush == nullptr)
            p_render_target->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush);

        return true;
    }


    // exit
    inline void Direct2d_Paint_Object::exit()
    {
        release(&brush);
        release(&p_render_target);
    }


    // Set Size
    inline void Direct2d_Paint_Object::resize()
    {
        ::GetClientRect(hwnd, &rect);
        D2D1_SIZE_U pixel_size = {
            (unsigned)(rect.right - rect.left),
            (unsigned)(rect.bottom - rect.top)
        };
        if (p_render_target != nullptr)
            p_render_target->Resize(pixel_size);
    }


    // Release
    template <class Interface>
    inline void Direct2d_Paint_Object::release(Interface** object)
    {
        if (*object != nullptr) {
            (*object)->Release();
            (*object) = nullptr;
        }
    }


    // Wether the Object is safe to use
    template <class Interface>
    inline bool Direct2d_Paint_Object::is_safe(Interface** object)
    {
        return ((p_factory != nullptr) && (p_write_factory != nullptr) && (p_render_target != nullptr) && ((*object) != nullptr));
    }
}