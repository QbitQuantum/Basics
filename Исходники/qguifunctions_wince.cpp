int qt_wince_GetDIBits(HDC /*hdc*/ , HBITMAP hSourceBitmap, uint, uint, LPVOID lpvBits, LPBITMAPINFO, uint)
{
    if (!lpvBits) {
        qWarning("::GetDIBits(), lpvBits NULL");
        return 0;
    }
    BITMAP bm;
    GetObject(hSourceBitmap, sizeof(BITMAP), &bm);
    bm.bmHeight = qAbs(bm.bmHeight);

    HBITMAP hTargetBitmap;
    void *pixels;

    BITMAPINFO dibInfo;
    memset(&dibInfo, 0, sizeof(dibInfo));
    dibInfo.bmiHeader.biBitCount = 32;
    dibInfo.bmiHeader.biClrImportant = 0;
    dibInfo.bmiHeader.biClrUsed = 0;
    dibInfo.bmiHeader.biCompression = BI_RGB;;
    dibInfo.bmiHeader.biHeight = -bm.bmHeight;
    dibInfo.bmiHeader.biWidth = bm.bmWidth;
    dibInfo.bmiHeader.biPlanes = 1;
    dibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    dibInfo.bmiHeader.biSizeImage = bm.bmWidth * bm.bmHeight * 4;

    HDC displayDC = GetDC(NULL);
    if (!displayDC) {
        qWarning("::GetDIBits(), failed to GetDC");
        return 0;
    }

    int ret = bm.bmHeight;

    hTargetBitmap = CreateDIBSection(displayDC, (const BITMAPINFO*) &dibInfo, DIB_RGB_COLORS,
                                    (void**)&pixels, NULL, 0);
    if (!hTargetBitmap) {
        qWarning("::GetDIBits(), failed to CreateDIBSection");
        return 0;
    }

    HDC hdcSrc = CreateCompatibleDC(displayDC);
    HDC hdcDst = CreateCompatibleDC(displayDC);

    if (!(hdcDst && hdcSrc)) {
        qWarning("::GetDIBits(), failed to CreateCompatibleDC");
        ret = 0;
    }

    HBITMAP hOldBitmap1 = (HBITMAP) SelectObject(hdcSrc, hSourceBitmap);
    HBITMAP hOldBitmap2 = (HBITMAP) SelectObject(hdcDst, hTargetBitmap);

    if (!(hOldBitmap1 && hOldBitmap2)) {
        qWarning("::GetDIBits(), failed to SelectObject for bitmaps");
        ret = 0;
    }

    if (!BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY)) {
        qWarning("::GetDIBits(), BitBlt failed");
        ret = 0;
    }

    SelectObject(hdcSrc, hOldBitmap1);
    SelectObject(hdcDst, hOldBitmap2);

    DeleteDC(hdcSrc);
    DeleteDC(hdcDst);

    ReleaseDC(NULL, displayDC);

    memcpy(lpvBits, pixels, dibInfo.bmiHeader.biSizeImage);

    DeleteObject(hTargetBitmap);
    return ret;
}