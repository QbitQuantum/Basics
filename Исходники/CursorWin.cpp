Cursor::Cursor(Image* img, const IntPoint& hotspot) 
{ 
    static bool doAlpha = supportsAlphaCursors();
    BITMAPINFO cursorImage = {0};
    cursorImage.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    cursorImage.bmiHeader.biWidth = img->width();
    cursorImage.bmiHeader.biHeight = img->height();
    cursorImage.bmiHeader.biPlanes = 1;
    cursorImage.bmiHeader.biBitCount = 32;
    cursorImage.bmiHeader.biCompression = BI_RGB;
    HDC dc = GetDC(0);
    HDC workingDC = CreateCompatibleDC(dc);
    if (doAlpha) {
        OwnPtr<HBITMAP> hCursor(CreateDIBSection(dc, (BITMAPINFO *)&cursorImage, DIB_RGB_COLORS, 0, 0, 0));
        ASSERT(hCursor);

        img->getHBITMAP(hCursor.get()); 
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(workingDC, hCursor.get());
        SetBkMode(workingDC, TRANSPARENT);
        SelectObject(workingDC, hOldBitmap);

        OwnPtr<HBITMAP> hMask(CreateBitmap(img->width(), img->height(), 1, 1, NULL));

        ICONINFO ii;
        ii.fIcon = FALSE;
        ii.xHotspot = hotspot.x();
        ii.yHotspot = hotspot.y();
        ii.hbmMask = hMask.get();
        ii.hbmColor = hCursor.get();

        m_impl = new SharedCursor(CreateIconIndirect(&ii));
    } else {
        // Platform doesn't support alpha blended cursors, so we need
        // to create the mask manually
        HDC andMaskDC = CreateCompatibleDC(dc);
        HDC xorMaskDC = CreateCompatibleDC(dc);
        OwnPtr<HBITMAP> hCursor(CreateDIBSection(dc, &cursorImage, DIB_RGB_COLORS, 0, 0, 0));
        ASSERT(hCursor);
        img->getHBITMAP(hCursor.get()); 
        BITMAP cursor;
        GetObject(hCursor.get(), sizeof(BITMAP), &cursor);
        OwnPtr<HBITMAP> andMask(CreateBitmap(cursor.bmWidth, cursor.bmHeight, 1, 1, NULL));
        OwnPtr<HBITMAP> xorMask(CreateCompatibleBitmap(dc, cursor.bmWidth, cursor.bmHeight));
        HBITMAP oldCursor = (HBITMAP)SelectObject(workingDC, hCursor.get());
        HBITMAP oldAndMask = (HBITMAP)SelectObject(andMaskDC, andMask.get());
        HBITMAP oldXorMask = (HBITMAP)SelectObject(xorMaskDC, xorMask.get());

        SetBkColor(workingDC, RGB(0,0,0));  
        BitBlt(andMaskDC, 0, 0, cursor.bmWidth, cursor.bmHeight, workingDC, 0, 0, SRCCOPY);
    
        SetBkColor(xorMaskDC, RGB(255, 255, 255));
        SetTextColor(xorMaskDC, RGB(255, 255, 255));
        BitBlt(xorMaskDC, 0, 0, cursor.bmWidth, cursor.bmHeight, andMaskDC, 0, 0, SRCCOPY);
        BitBlt(xorMaskDC, 0, 0, cursor.bmWidth, cursor.bmHeight, workingDC, 0,0, SRCAND);

        SelectObject(workingDC, oldCursor);
        SelectObject(andMaskDC, oldAndMask);
        SelectObject(xorMaskDC, oldXorMask);

        ICONINFO icon = {0};
        icon.fIcon = FALSE;
        icon.xHotspot = hotspot.x();
        icon.yHotspot = hotspot.y();
        icon.hbmMask = andMask.get();
        icon.hbmColor = xorMask.get();
        m_impl = new SharedCursor(CreateIconIndirect(&icon));

        DeleteDC(xorMaskDC);
        DeleteDC(andMaskDC);
    }
    DeleteDC(workingDC);
    ReleaseDC(0, dc);
}