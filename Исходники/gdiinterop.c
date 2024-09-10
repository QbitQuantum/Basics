static HRESULT WINAPI gdiinterop_CreateFontFaceFromHdc(IDWriteGdiInterop *iface,
    HDC hdc, IDWriteFontFace **fontface)
{
    struct gdiinterop *This = impl_from_IDWriteGdiInterop(iface);
    IDWriteFont *font;
    LOGFONTW logfont;
    HFONT hfont;
    HRESULT hr;

    TRACE("(%p)->(%p %p)\n", This, hdc, fontface);

    *fontface = NULL;

    hfont = GetCurrentObject(hdc, OBJ_FONT);
    if (!hfont)
        return E_INVALIDARG;
    GetObjectW(hfont, sizeof(logfont), &logfont);

    hr = IDWriteGdiInterop_CreateFontFromLOGFONT(iface, &logfont, &font);
    if (FAILED(hr))
        return hr;

    hr = IDWriteFont_CreateFontFace(font, fontface);
    IDWriteFont_Release(font);

    return hr;
}