// based on http://theartofdev.wordpress.com/2013/10/24/transparent-text-rendering-with-gdi/,
// TODO: look into using http://theartofdev.wordpress.com/2014/01/12/gdi-text-rendering-to-image/
// TODO: doesn't actually look good (i.e. similar to DrawText when using transparent SetBkMode())
// which kind of makes sense, because I'm using transparent mode to draw to in-memory bitmap as well
// TODO: doesn't actually do alpha bf.SourceConstantAlpha > 4 looks the same, values 1-4 produce
// different, but not expected, results
// TODO: the bitmap should be cached so that we don't call CreateDIBSection every time
// TODO: I would like to figure out a way to draw text without the need to Lock()/Unlock()
// maybe draw to in-memory bitmap, convert to Graphics bitmap and blit that bitmap to
// Graphics object
void TextRenderGdi::DrawTransparent(const WCHAR *s, size_t sLen, RectF& bb, bool isRtl) {
    CrashIf(!hdcGfxLocked); // hasn't been Lock()ed
    //SetBkMode(hdcGfxLocked, 1);

    HDC memHdc = CreateCompatibleDC(hdcGfxLocked);
    SetBkMode(memHdc, TRANSPARENT);
    int x = (int) bb.X;
    int y = (int) bb.Y;
    int dx = (int) bb.Width;
    int dy = (int) bb.Height;

    BITMAPINFO bmi = { };
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = dx;
    bmi.bmiHeader.biHeight = dy;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = dx * dy * 4; // doesn't seem necessary?

    unsigned char *bmpData = NULL;
    HBITMAP dib = CreateDIBSection(memHdc, &bmi, DIB_RGB_COLORS, (void **)&bmpData, NULL, 0);
    if (!dib)
        return;
    memset(bmpData, 0, bmi.bmiHeader.biSizeImage);
    SelectObject(memHdc, dib);
    //BitBlt(memHdc, 0, 0, dx, dy, hdcGfxLocked, x, y, SRCCOPY);
    SelectObject(memHdc, currFont);
    ::SetTextColor(memHdc, textColor.ToCOLORREF());

#if 0
    TextOut(memHdc, 0, 0, s, sLen);
#else
    UINT opts = 0; //ETO_OPAQUE;
    if (isRtl)
        opts = opts | ETO_RTLREADING;
    ExtTextOutW(memHdc, 0, 0, opts, NULL, s, (int)sLen, NULL);
#endif

    BLENDFUNCTION bf = {};
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = 0; // 0 - ignore source alpha, AC_SRC_ALPHA (1) - use source alpha
    bf.SourceConstantAlpha = 0x3; //textColor.GetA();
    AlphaBlend(hdcGfxLocked, x, y, dx, dy, memHdc, 0, 0, dx, dy, bf);
    DeleteObject(dib);
    DeleteDC(memHdc);
}