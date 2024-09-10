HRESULT IconBitmapUtils::ConvertBufferToPARGB32(HPAINTBUFFER hPaintBuffer, HDC hdc, HICON hicon, SIZE& sizIcon)
{
    RGBQUAD *prgbQuad;
    int cxRow;
    HRESULT hr = GetBufferedPaintBits(hPaintBuffer, &prgbQuad, &cxRow);
    if (FAILED(hr))
        return hr;

    Gdiplus::ARGB *pargb = reinterpret_cast<Gdiplus::ARGB *>(prgbQuad);
    if (HasAlpha(pargb, sizIcon, cxRow))
        return S_OK;

    ICONINFO info;
    if (!GetIconInfo(hicon, &info))
        return S_OK;
    SCOPE_EXIT
    {
        DeleteObject(info.hbmColor);
        DeleteObject(info.hbmMask);
    };
    if (info.hbmMask)
        return ConvertToPARGB32(hdc, pargb, info.hbmMask, sizIcon, cxRow);

    return S_OK;
}