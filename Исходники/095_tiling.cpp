HBRUSH CreatePatternBrushFromFile(LPCTSTR pszFile)
{
    HBRUSH hbr = NULL;
    HBITMAP hbm = (HBITMAP)LoadImage(g_hinst, pszFile,
                   IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hbm) {
        hbr = CreatePatternBrush(hbm);
        DeleteObject(hbm);
    }
    return hbr;
}