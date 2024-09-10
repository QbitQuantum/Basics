void Graphics::drawText(const char_t* text, ulong_t length, const Point& topLeft, bool inverted)
{
    FontEffects fx = font_.effects();    
    PalmUnderlineSetter setUnderline(convertUnderlineMode(fx.underline()));

    ScalingSetter setScaling(*this);

    uint_t height = fontHeight();
    uint_t top=topLeft.y;
    if (fx.subscript())
        top+=(height/3);
    if (inverted)
        WinDrawInvertedChars(text, length, topLeft.x, top);
    else         
        WinDrawChars(text, length, topLeft.x, top);

    if (fx.strikeOut())
    {
        uint_t baseline = fontBaseline();
        top=topLeft.y + (baseline*2)/3;
        uint_t width = FntCharsWidth(text, length);
        Color_t color=setTextColor(0);
        setTextColor(color); // Quite strange method of querying current text color...
        color=setForegroundColor(color);
        WinDrawOperation old;
        if (inverted)
            old=WinSetDrawMode(winInvert);
        drawLine(topLeft.x, top, topLeft.x+width, top);
        if (inverted)
            WinSetDrawMode(old);
        setForegroundColor(color);
    }
  }