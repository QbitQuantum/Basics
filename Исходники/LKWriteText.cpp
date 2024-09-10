void MapWindow::LKWriteText(LKSurface& Surface, const TCHAR* wText, int x, int y,
        const bool lwmode, const short align, const LKColor& rgb_text, bool invertable, RECT* ClipRect) {

    SIZE tsize;

    Surface.GetTextSize(wText, &tsize);
    LKColor textColor = rgb_text;
    // by default, LK8000 is white on black, i.e. inverted
    if ((!INVERTCOLORS) || (LKTextBlack && invertable)) {
        const Color2Color_t* It = std::find_if(std::begin(ColorInvert), std::end(ColorInvert),
                                                std::bind(
                                                    std::equal_to< Color2Color_t::first_type >(),
                                                    std::bind(&Color2Color_t::first, _1), textColor));

        if (It != std::end(ColorInvert)) {
            textColor = It->second;
        }
    }

    switch (align) {
        case WTALIGN_RIGHT:
            x -= tsize.cx;
            break;
        case WTALIGN_CENTER:
            x -= tsize.cx / 2;
            y -= tsize.cy / 2;
            break;
    }
    //rgb_text=RGB_MAGENTA;
    bool moreoutline = false;

    Surface.SetBackgroundTransparent();

    if(lwmode) { // WTMODE_OUTLINED:
        //
        // First set a background color for outlining
        // black outline requires more width, to gain contrast.
        //

        const Color2Outline_t* It = std::find_if(std::begin(ColorOutLine), std::end(ColorOutLine),
                                                    std::bind(
                                                        std::equal_to<Color2Outline_t::first_type>(),
                                                        std::bind(&Color2Outline_t::first, _1), textColor));
        if (It != std::end(ColorOutLine)) {
            // Here we invert colors, looking at the foreground. The trick is that the foreground
            // colour is slightly different white to white, in order to understand how to invert it
            // correctly!
            Surface.SetTextColor(It->second.first);
            moreoutline = It->second.second;
        } else {
            // this is the default also for white text. Normally we are writing on a
            // not-too-light background
            Surface.SetTextColor(RGB_BLACK);
            moreoutline = true;
        }

        //
        // Simplified, shadowing better and faster
        // ETO_OPAQUE not necessary since we pass a NULL rect
        //
#ifdef USE_FREETYPE
#warning "to slow, rewrite using freetype outline"
#endif

#if !defined(PNA) || !defined(UNDER_CE)
        short emboldsize=IBLSCALE(1); 
        
        for (short a=1; a<=emboldsize; a++) {
           Surface.DrawText(x - a, y - a, wText, ClipRect);
           Surface.DrawText(x - a, y + a, wText, ClipRect);
           Surface.DrawText(x + a, y - a, wText, ClipRect);
           Surface.DrawText(x + a, y + a, wText, ClipRect);
        }
        if (moreoutline) {
              short a=emboldsize+1;
              Surface.DrawText(x - a, y, wText, ClipRect);
              Surface.DrawText(x + a, y, wText, ClipRect);
              Surface.DrawText(x, y - a, wText, ClipRect);
              Surface.DrawText(x, y + a, wText, ClipRect);
        }
#else
        Surface.DrawText(x - 1, y - 1, wText, ClipRect);
        Surface.DrawText(x - 1, y + 1, wText, ClipRect);
        Surface.DrawText(x + 1, y - 1, wText, ClipRect);
        Surface.DrawText(x + 1, y + 1, wText, ClipRect);

        // SetTextColor(hDC,RGB_GREY);  // This would give an Emboss effect
        // Surface.DrawText(x, y+2, 0, wText, maxsize);

        if (moreoutline) {
            Surface.DrawText(x - 2, y, wText, ClipRect);
            Surface.DrawText(x + 2, y, wText, ClipRect);
            Surface.DrawText(x, y - 2, wText, ClipRect);
            Surface.DrawText(x, y + 2, wText, ClipRect);
        }
#endif

        Surface.SetTextColor(textColor);
        Surface.DrawText(x, y, wText, ClipRect);
        Surface.SetTextColor(RGB_BLACK);

    } else { // WTMODE_NORMAL:

        Surface.SetTextColor(textColor);
        Surface.DrawText(x, y, wText, ClipRect);
        Surface.SetTextColor(RGB_BLACK);

    }

    return;

}