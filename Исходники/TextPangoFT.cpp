void Gosu::pango::drawText(Bitmap& bitmap, const std::wstring& text, int x, int y,
    Color c, const std::wstring& fontFace, unsigned fontHeight,
    unsigned fontFlags)
{
    textWidth(text, fontFace, fontHeight, fontFlags);

    FT_Bitmap ft_bitmap;

    guchar* buf = new guchar[width * height];
    std::fill(buf, buf + width * height, 0x00);

    ft_bitmap.rows = height;
    ft_bitmap.width = width;
    ft_bitmap.pitch = ft_bitmap.width;
    ft_bitmap.buffer = buf;
    ft_bitmap.num_grays = 256;
    ft_bitmap.pixel_mode = ft_pixel_mode_grays;

    int x_start = 0;
    pango_ft2_render_layout(&ft_bitmap, layout, x_start, 0);


    int min_height = height;
    if((unsigned)height > fontHeight) min_height = fontHeight;

    for(int y2 = 0; y2 < min_height; y2++)
    {
        if (y + y2 < 0 || y + y2 >= bitmap.height())
            break;
        
        for(int x2 = 0; x2 < width; x2++)
        {
            if (x + x2 < 0 || x + x2 >= bitmap.width())
                break;
            unsigned val = ft_bitmap.buffer[y2*width+x2];
            Color color = c;
            color.setAlpha(val);
            bitmap.setPixel(x2 + x, y2 + y, color);
        }
    }

    delete[] buf;
}