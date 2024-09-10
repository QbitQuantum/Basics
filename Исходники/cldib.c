int SmartStretchDIBits(
    HDC          hdc,
    int          xD,
    int          yD,
    int          dxD,
    int          dyD,
    int          xS,
    int          yS,
    int          dxS,
    int          dyS,
    LPVOID       lpBits,
    LPBITMAPINFO lpbi,
    UINT         wUsage,
    DWORD        rop)
{
    LPBYTE             lpBitsNew;
    UINT               bpp;
    RGBQUAD            rgb;
    LPBITMAPINFOHEADER lpbiNew = NULL;

    int i;

    /*
     * thunk to USER32
     */
    UserAssert(rop == SRCCOPY);
    UserAssert(wUsage == DIB_RGB_COLORS);
    UserAssert(xS == 0 && yS == 0);

    if ((GetDIBColorTable(hdc, 0, 1, &rgb) != 1) &&
        (dxD != dxS || dyD != dyS) &&           // 1:1 stretch just call GDI
        (dxD >= dxS/2) && (dyD >= dyS/2) &&     // less than 1:2 shrink call GDI
        (lpbi->bmiHeader.biCompression == 0) && // must be un-compressed
        (lpbi->bmiHeader.biBitCount == 4 ||     // input must be 4,8,24
         lpbi->bmiHeader.biBitCount == 8 ||
         lpbi->bmiHeader.biBitCount == 24)) {

        bpp = GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES);

        bpp = (bpp > 8 ? 24 : 8);

        lpbiNew = (LPBITMAPINFOHEADER)UserLocalAlloc(0,
                 sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)) +
                 (UINT)((((dxD * bpp) / 8) + 3) & ~3) * (UINT)dyD);

        if (lpbiNew) {

            *lpbiNew            = lpbi->bmiHeader;
            lpbiNew->biWidth    = dxD;
            lpbiNew->biHeight   = dyD;
            lpbiNew->biBitCount = bpp;
            lpBitsNew = (LPBYTE)lpbiNew          +
                        sizeof(BITMAPINFOHEADER) +
                        (256 * sizeof(RGBQUAD));

            if (ScaleDIB((LPBITMAPINFOHEADER)lpbi,
                         (LPVOID)lpBits,
                         lpbiNew,
                         lpBitsNew)) {

                lpbi   = (LPBITMAPINFO)lpbiNew;
                lpBits = lpBitsNew;
                dxS    = dxD;
                dyS    = dyD;
            }
        }
    }

    i = StretchDIBits(hdc,
                      xD,
                      yD,
                      dxD,
                      dyD,
                      xS,
                      yS,
                      dxS,
                      dyS,
                      lpBits,
                      lpbi,
                      wUsage,
                      rop);

    if (lpbiNew)
        UserLocalFree(lpbiNew);

    return i;
}