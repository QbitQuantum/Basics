BOOL GUIAPI SaveMainWindowContent (HWND hWnd, const char* filename)
{
    RECT rcScreen;
    RECT rcWin;
    BITMAP bitmap;
    int save_ret;

    SetRect (&rcScreen, 0, 0, WIDTHOFPHYGC, HEIGHTOFPHYGC);
    if (hWnd) {
        GetWindowRect (hWnd, &rcWin);
        if (!IntersectRect (&rcWin, &rcWin, &rcScreen))
            return FALSE;
    }
    else
        rcWin = rcScreen;

    bitmap.bmType = BMP_TYPE_NORMAL;
    bitmap.bmBitsPerPixel = BITSPERPHYPIXEL;
    bitmap.bmBytesPerPixel = BYTESPERPHYPIXEL;
    bitmap.bmWidth = RECTW (rcWin);
    bitmap.bmHeight = RECTH (rcWin);
    bitmap.bmPitch = bitmap.bmWidth * bitmap.bmBytesPerPixel;

    if (bitmap.bmWidth == 0 || bitmap.bmHeight == 0) {
#ifdef _DEBUG
        fprintf (stderr, "SaveContent: Empty Rect.\n");
#endif
        return FALSE;
    }
    
    bitmap.bmBits = SaveCoveredScreenBox (rcWin.left, rcWin.top, 
                                    RECTW (rcWin), RECTH (rcWin));
    if (!bitmap.bmBits) {
#ifdef _DEBUG
        fprintf (stderr, "SaveContent: SaveBox error.\n");
#endif
        return FALSE;
    }
    
    save_ret = SaveBitmap (HDC_SCREEN, &bitmap, filename);
    free (bitmap.bmBits);
    return (save_ret == 0);
}