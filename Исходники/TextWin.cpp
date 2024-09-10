void Gosu::drawText(Bitmap& bitmap, const std::wstring& text, int x, int y,
    Color c, const std::wstring& fontName, unsigned fontHeight,
    unsigned fontFlags)
{
    unsigned width = textWidth(text, fontName, fontHeight, fontFlags);

    WinBitmap helper(width, fontHeight);
    helper.selectFont(fontName, fontHeight, fontFlags);

    if (::SetTextColor(helper.context(), 0xffffff) == CLR_INVALID)
        Win::throwLastError("setting the text color");

    Win::check(::SetBkMode(helper.context(), TRANSPARENT),
        "setting a bitmap's background mode to TRANSPARENT");

    ::ExtTextOut(helper.context(), 0, 0, 0, 0, text.c_str(), text.length(), 0);
    
    for (unsigned relY = 0; relY < fontHeight; ++relY)
        for (unsigned relX = 0; relX < width; ++relX)
        {
            Color pixel = c;
            Color::Channel srcAlpha = GetPixel(helper.context(), relX, relY) & 0xff;
            pixel = multiply(c, Color(srcAlpha, 255, 255, 255));
            if (pixel != 0 && x + relX >= 0 && x + relX < bitmap.width() &&
                y + relY >= 0 && y + relY < bitmap.height())
                bitmap.setPixel(x + relX, y + relY, pixel);
        }
}