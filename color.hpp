//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Point)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"



namespace aului {
    struct Color {
        static constexpr int MAX = 255;
        int r, g, b;

        inline bool operator == (const Color& col) const
        {
            return this->r == col.r && this->g == col.g && this->b == col.b;
        }

        inline void operator = (COLORREF colr)
        {
            this->r = GetRValue(colr);
            this->g = GetGValue(colr);
            this->b = GetBValue(colr);
        }

        inline Color operator + (const Color& col) const
        {
            return {
                this->r + col.r,
                this->g + col.g,
                this->b + col.b
            };
        }

        inline Color operator - (const Color& col) const
        {
            return {
                this->r - col.r,
                this->g - col.g,
                this->b - col.b
            };
        }

        Color(int _r = 0, int _g = 0, int _b = 0) :
            r(_r), g(_g), b(_b)
        {}

        void invert();
        void change_color(int r_, int g_, int b_);
        void change_brightness(int val);
        void change_contrast(double val);
        void to_bgr();
        COLORREF colorref() const;
        UINT32 d2dcolor() const;
    };


    inline void Color::invert()
    {
        r = MAX - r;
        g = MAX - g;
        b = MAX - b;
    }

    inline void Color::change_color(int r_, int g_, int b_)
    {
        r = r_;
        g = g_;
        b = b_;
    }

    inline void Color::change_brightness(int val)
    {
        r += val;
        g += val;
        b += val;
    }

    inline void Color::change_contrast(double val)
    {
        r = 127 + (int)((r - 127) * val);
        g = 127 + (int)((g - 127) * val);
        b = 127 + (int)((b - 127) * val);
    }

    inline void Color::to_bgr()
    {
        int tmp = r;
        r = b;
        b = tmp;
    }

    inline COLORREF Color::colorref() const
    {
        return RGB(
            std::clamp(r, 0, MAX),
            std::clamp(g, 0, MAX),
            std::clamp(b, 0, MAX)
        );
    }

    inline UINT32 Color::d2dcolor() const
    {
        return RGB(
            std::clamp(b, 0, MAX),
            std::clamp(g, 0, MAX),
            std::clamp(r, 0, MAX)
        );
    }
}