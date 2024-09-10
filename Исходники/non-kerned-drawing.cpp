void drawTextWithSpacing(GraphicsContext* graphicsContext, const SimpleFontData* font, const wxColour& color, const GlyphBuffer& glyphBuffer, int from, int numGlyphs, const FloatPoint& point)
{
#if USE(WXGC)
    wxGCDC* dc = static_cast<wxGCDC*>(graphicsContext->platformContext());
#else
    wxDC* dc = graphicsContext->platformContext();
#endif

    // get the native HDC handle to draw using native APIs
    HDC hdc = 0;
#if USE(WXGC)
    wxGraphicsContext* gc = dc->GetGraphicsContext();
    Gdiplus::Graphics* g;
    if (gc) {
        g = (Gdiplus::Graphics*)gc->GetNativeContext();
        hdc = g->GetHDC();
    }
#else
    hdc = static_cast<HDC>(dc->GetHDC());
#endif

    // ExtTextOut wants the offsets as an array of ints, so extract them
    // from the glyph buffer
    const GlyphBufferGlyph*   glyphs   = glyphBuffer.glyphs(from);
    const GlyphBufferAdvance* advances = glyphBuffer.advances(from);

    float y = point.y() - font->ascent();
    float x = point.x();

    int* spacing = new int[numGlyphs - from];
    for (unsigned i = 0; i < numGlyphs; ++i)
        spacing[i] = advances[i].width();

    wxFont* wxfont = font->getWxFont();
    if (wxfont && wxfont->IsOk())
        ::SelectObject(hdc, GetHfontOf(*wxfont));

    if (color.Ok())
        ::SetTextColor(hdc, color.GetPixel());

    // do not draw background behind characters
    ::SetBkMode(hdc, TRANSPARENT);

    // draw text with optional character widths array
    wxString string = wxString((wxChar*)(&glyphs[from]), numGlyphs);
    ::ExtTextOut(hdc, x, y, 0, NULL, string.c_str(), string.length(), spacing);

    ::SetBkMode(hdc, TRANSPARENT);

    #if USE(WXGC)
        g->ReleaseHDC(hdc);
    #endif

    delete [] spacing;
}