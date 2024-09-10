STATICFN HBITMAP LoadAlterBitmap(
    INT idbm,
    DWORD rgbNew,
    DWORD rgbNew2)
{
    register INT i;
    LPBITMAPINFOHEADER lpbihInfo;
    HDC hdcScreen;
    HANDLE hresLoad;
    DWORD FAR *qlng;
    LPBYTE lpbBits;
    HANDLE hbmp;
    DWORD rgbReplace1;
    DWORD rgbReplace2;

    hresLoad = FindResource(ghInst, MAKEINTRESOURCE(idbm), RT_BITMAP);
    if (!hresLoad)
        return NULL;

    lpbihInfo = (LPBITMAPINFOHEADER)CloneResource(ghInst, hresLoad);
    if (lpbihInfo == NULL)
        return NULL;

    rgbNew = RGBInvertRGB(rgbNew);
    rgbNew2 = RGBInvertRGB(rgbNew2);
    rgbReplace1 = RGBInvertRGB(REPLACECOLOR1);
    rgbReplace2 = RGBInvertRGB(REPLACECOLOR2);
    qlng = (LPDWORD)((PBYTE)(lpbihInfo) + lpbihInfo->biSize);

    for (i = 0; i < (1 << lpbihInfo->biBitCount); i++, qlng++) {
        if (*qlng == rgbReplace1)
            *qlng = rgbNew;
        else if (*qlng == rgbReplace2)
            *qlng = rgbNew2;
    }

    /*
     * First skip over the header structure.
     */
    lpbBits = (LPBYTE)(lpbihInfo + 1);

    /*
     * Skip the color table entries, if any.
     */
    lpbBits += (1 << (lpbihInfo->biBitCount)) * sizeof(RGBQUAD);

    /*
     * Create a color bitmap compatible with the display device.
     */
    if (hdcScreen = GetDC(NULL)) {
        hbmp = CreateDIBitmap(hdcScreen, lpbihInfo, (LONG)CBM_INIT,
                lpbBits, (LPBITMAPINFO)lpbihInfo, DIB_RGB_COLORS);
        ReleaseDC(NULL, hdcScreen);
    }

    LocalFree(lpbihInfo);

    return hbmp;
}