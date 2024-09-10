VOID
AdjustBrightness(HBITMAP hOrigBitmap,
                 HBITMAP hNewBitmap,
                 HWND hwnd,
                 HDC hdcMem,
                 INT RedVal,
                 INT GreenVal,
                 INT BlueVal)
{
    BITMAPINFO bi;
    BITMAP bitmap;
    BOOL bRes;
    DWORD Count = 0;
    INT i, j;
    PBYTE pBits;
    RECT rc;

    GetObject(hNewBitmap,
              sizeof(BITMAP),
              &bitmap);

    /* Bitmap header */
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = bitmap.bmWidth;
    bi.bmiHeader.biHeight = bitmap.bmHeight;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biSizeImage = bitmap.bmWidth * bitmap.bmHeight * 4;
    bi.bmiHeader.biClrUsed = 0;
    bi.bmiHeader.biClrImportant = 0;

    /* Buffer */
    pBits = (PBYTE)HeapAlloc(ProcessHeap,
                             0,
                             bitmap.bmWidth * bitmap.bmHeight * 4);
    if (!pBits)
        return;

    /* get the bits from the original bitmap */
    bRes = GetDIBits(hdcMem,
                     hOrigBitmap,
                     0,
                     bitmap.bmHeight,
                     pBits,
                     &bi,
                     DIB_RGB_COLORS);

    for (i = 0; i < bitmap.bmHeight; i++)
    {
        for (j = 0; j < bitmap.bmWidth; j++)
        {
            DWORD Val = 0;
            INT b, g, r;

            CopyMemory(&Val,
                       &pBits[Count],
                       4);

            /* Get pixels in reverse order */
            b = GetRValue(Val);
            g = GetGValue(Val);
            r = GetBValue(Val);

            /* Red */
            r += RedVal;
            if (r > 255) r = 255;
            else if (r < 0) r = 0;

            /* Green */
            g += GreenVal;
            if (g > 255) g = 255;
            else if (g < 0) g = 0;

            /* Blue */
            b += BlueVal;
            if (b > 255) b = 255;
            else if (b < 0) b = 0;

            /* Store in reverse order */
            Val = RGB(b, g, r);
            CopyMemory(&pBits[Count],
                       &Val,
                       4);

            /* RGB color take 4 bytes.The high-order byte must be zero */
            Count += 4;
        }
    }

    /* Set the new pixel bits */
    SetDIBits(hdcMem,
              hNewBitmap,
              0,
              bRes,
              pBits,
              &bi,
              DIB_RGB_COLORS);

    HeapFree(ProcessHeap,
             0,
             pBits);

    GetClientRect(hwnd,
                  &rc);

    InvalidateRect(hwnd,
                   &rc,
                   FALSE);
}