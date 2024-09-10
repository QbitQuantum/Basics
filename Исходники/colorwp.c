STATICFN DWORD NEAR ComputeInverseColor(
    DWORD rgb)
{
    HBITMAP hTempBit1;
    HBITMAP hTempBit2;
    HDC hTempDC1;
    HDC hTempDC2;
    HDC hdc;
    HANDLE hOldObj1;
    HANDLE hOldObj2;
    DWORD rgbInv;

    hdc = GetDC(ghwndMain);
    hTempDC1 = CreateCompatibleDC(hdc);
    hTempDC2 = CreateCompatibleDC(hdc);

    /* create two temporary 1x1, 16 color bitmaps */
    hTempBit1 = MyCreateBitmap(hdc, 1, 1, 16);
    hTempBit2 = MyCreateBitmap(hdc, 1, 1, 16);

    ReleaseDC(ghwndMain, hdc);

    hOldObj1 = SelectObject(hTempDC1, hTempBit1);
    hOldObj2 = SelectObject(hTempDC2, hTempBit2);

    /* method for getting inverse color : set the given pixel (rgb) on
     * one DC. Now blt it to the other DC using a SRCINVERT rop.
     * This yields a pixel of the inverse color on the destination DC
     */
    SetPixel(hTempDC1, 0, 0, rgb);
    PatBlt(hTempDC2, 0, 0, 1, 1, WHITENESS);
    BitBlt(hTempDC2, 0, 0, 1, 1, hTempDC1, 0, 0, SRCINVERT);
    rgbInv = GetPixel(hTempDC2, 0, 0);

    /* clean up ... */
    SelectObject(hTempDC1, hOldObj1);
    SelectObject(hTempDC2, hOldObj2);
    DeleteObject(hTempBit1);
    DeleteObject(hTempBit2);
    DeleteDC(hTempDC1);
    DeleteDC(hTempDC2);

    /* ...and return the inverted RGB value */
    return rgbInv;
}