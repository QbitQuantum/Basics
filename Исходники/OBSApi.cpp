static LPBYTE GetBitmapData(HBITMAP hBmp, BITMAP &bmp)
{
    if (!hBmp)
        return NULL;

    if (GetObject(hBmp, sizeof(bmp), &bmp) != 0) {
        UINT bitmapDataSize = bmp.bmHeight*bmp.bmWidth*bmp.bmBitsPixel;
        bitmapDataSize >>= 3;

        LPBYTE lpBitmapData = (LPBYTE)Allocate(bitmapDataSize);
        GetBitmapBits(hBmp, bitmapDataSize, lpBitmapData);

        return lpBitmapData;
    }