//----------------------------------------------------------------------------------
//		Common UI Library for AviUtl Plugins
//		Header File (Image)
//		made by mimaraka
//----------------------------------------------------------------------------------

#pragma once

#include "common.hpp"



namespace aului {
    class Image_PNG {
    public:
        IWICBitmapDecoder* p_wic_bitmap_decoder = nullptr;
        IWICBitmapFrameDecode* p_wic_bitmap_frame = nullptr;
        IWICFormatConverter* p_format_converter = nullptr;
        ID2D1Bitmap* p_bitmap = nullptr;

    protected:
        IWICImagingFactory* p_image_factory;
    };
}